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

#ifndef __TTFOAMINTERFACE_H__
#define __TTFOAMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TTFLink.h"
#include "PsTypeDef.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define GRM_MNTN_TS_TOTAL                           (8)    /* ʱ϶������ts0-ts7��8�� */
#define GRLC_MNTN_MAX_TBF_NUM                       (1)    /* ��ǰ֧�ֵ����TBF���Ϊ1����֧�ֶ�TBF */
#define  WTTF_MNTN_MAX_AM_RB_NUM                    (8)    /* 3��AMҵ��RB,���RB2-RB4 ��������RB,����6��AM RB. 25.306 R9Э��Table 5.1b������8��AM RB */
#define  WTTF_MNTN_MAX_TM_RB_NUM                    (4)    /* TM RB����,RB0������, 3��AMR����RB + 1��TM CSD����4��TM RB, */
#define  WTTF_MNTN_MAX_UM_RB_NUM                    (6)    /* UM RB����, CBS����Ӧ��RB��RB0������,GCF����Ҫ����������UMҵ��RB,RB1ΪUM����RB,����3��UM RB ����AMʵ�������Ӧ*/

#define  WTTF_MNTN_MAX_RB_ID                        (32)    /* INTEGER (1..32) */
#define  WTTF_MNTN_MAX_FLX_RLC_SIZE_LEVEL_CNT       (10) /*�����ñ䳤SIZE��λ��*/
#define  WTTF_MNTN_RLC_AM_MAX_SN_NUM                (4096)

/* ���͵�RLPʵ��ĸ��� */
#define CTTF_HRPD_MNTN_DEFAULT_RLP_MAX_NUM   (2)

/* MFPA RLPʵ��������� */
#define CTTF_HRPD_MNTN_MF_RLP_MAX_NUM        (6)

/* EMPA RLPʵ��������� */
#define CTTF_HRPD_MNTN_EMF_RLP_MAX_NUM       (6)

/* ����CDMA 5.12s����, ����ÿ1.28s�ϱ�һ�Ρ�1.28s=64*20ms, 64��Ϊ�����±�,
��һ���ϱ�64֡�������, �ڴ���Խ��� */
#define   CTTF_1X_MAC_MNTN_MAX_REPORT_NUM    (64)

/* ��ΪHIDS��֧�ֶ�̬��ӡ�ɾ��RLPʵ��, �������ۺ��������Э�����ֵ���� */
#define    CTTF_1X_RLP_MNTN_MAX_NUM    (6)

/* �ϱ���MAC�����������ο������� */
#define   CTTF_HRPD_RTC3MAC_MNTN_FLOW_MAX_NUM   (8)

/*
    ����Э��16slotΪһ��MAC Layer Packet, ÿһ����֡��¼һ�Ρ�һ����֡Ϊ4��slot,
    ��16��slot�����16/4=4������һ��slotΪ1.28ms����ô16��slot��Ӧ26.66ms��
    ��Ϊ640ms�ϱ�һ����Ϣ����ô��Ϣ��һ��MAC���������24�����ݣ�640=48*26.66ms����
    һ�����ݼ�¼4����֡����Ϣ����1.28s��ÿ�����ϱ�24*4= 96�顣
*/
#define   CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_PACKET_PER_FLOW     (96)
#define   CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_T2P_PER_FLOW        (96)
#define   CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_HARQ                (96)


/**
 * It's define the num of  subframe information instances
 */
#define CTTF_HRPD_MNTN_NUM_SUBFRAME_INFO_INSTANCES              (3)

/* rtc3֧�ֵ����֯(����)�� */
#define CTTF_HRPD_MNTN_RTC3MAC_INTERLACE_MAX_NUM       (3)


/* ����PID��Χ */
#define IS_WUEPS_PID_RABM(x)            ((I0_WUEPS_PID_RABM == x) || (I1_WUEPS_PID_RABM == x) || (I2_WUEPS_PID_RABM == x))
#define IS_WUEPS_PID_PDCP(x)            (WUEPS_PID_PDCP == x)
#define IS_WUEPS_PID_RLC(x)             (WUEPS_PID_RLC == x)
#define IS_WUEPS_PID_MAC(x)             (WUEPS_PID_MAC == x)
#define IS_WUEPS_PID_WAS(x)             ((WUEPS_PID_WRR == x) || (WUEPS_PID_WCOM == x))
#define IS_UEPS_PID_SN(x)               ((I0_UEPS_PID_SN == x) || (I1_UEPS_PID_SN == x) || (I2_UEPS_PID_SN == x))
#define IS_UEPS_PID_LL(x)               ((I0_UEPS_PID_LL == x) || (I1_UEPS_PID_LL == x) || (I2_UEPS_PID_LL == x))
#define IS_UEPS_PID_GRM(x)              ((I0_UEPS_PID_GRM == x) || (I1_UEPS_PID_GRM == x) || (I2_UEPS_PID_GRM == x))
#define IS_UEPS_PID_DL(x)               ((I0_UEPS_PID_DL == x) || (I1_UEPS_PID_DL == x) || (I2_UEPS_PID_DL == x))
#define IS_UEPS_PID_MM(x)               ((I0_WUEPS_PID_MM == x) || (I1_WUEPS_PID_MM == x) || (I2_WUEPS_PID_MM == x))
#define IS_UEPS_PID_SMS(x)              ((I0_WUEPS_PID_SMS == x) || (I1_WUEPS_PID_SMS == x) || (I2_WUEPS_PID_SMS == x))
#define IS_UEPS_PID_GAS(x)              ((I0_UEPS_PID_GAS == x) || (I1_UEPS_PID_GAS == x) || (I2_UEPS_PID_GAS == x))
#define IS_UEPS_PID_GPHY(x)             ((I0_DSP_PID_GPHY == x) || (I1_DSP_PID_GPHY == x) || (I2_DSP_PID_GPHY == x))


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : TTF_MNTN_MSG_TYPE_ENUM
 ö��˵��  : ��ά�ɲ���Ϣ����(͸����Ϣ), �����е�͸����Ϣ��ID������������
*****************************************************************************/
enum TTF_MNTN_MSG_TYPE_ENUM
{
/*****************************************************************************
    TTF��͸����ϢĿǰ��������MODEM
*****************************************************************************/

    /* Wģ��ά�ɲ���Ϣ�ı����DO��ͷ */
    ID_OM_WTTF_RLC_DATA_TRANS_INFO_REQ          = 0xD001,    /*Wģ��RLC ʵ����Ϣ�ϱ�����,���й�����AM��UM��TM����ģʽ�������û�������ȫ���򲿷���ʾ*/
    ID_WTTF_OM_RLC_DATA_TRANS_INFO_CNF          = 0xD002,    /*Wģ��RLC ʵ����Ϣ�ϱ��ظ�*/
    ID_WTTF_OM_RLC_DATA_TRANS_INFO_IND          = 0xD003,    /*Wģ��RLC ʵ����Ϣ�ϱ�ָʾ*/
    ID_OM_WTTF_ADVANCED_TRACE_CONFIG_REQ        = 0xD004,    /*Wģ��Trace �߼�����*/
    ID_WTTF_OM_ADVANCED_TRACE_CONFIG_CNF        = 0xD005,    /*Wģ��Trace �߼�����ָʾ*/
    ID_OM_WTTF_RLC_PDU_SIZE_TRANS_INFO_REQ      = 0xD006,    /*Wģ��RLC PDU SIZEͳ����Ϣ�ϱ�����*/
    ID_WTTF_OM_RLC_PDU_SIZE_TRANS_INFO_CNF      = 0xD007,    /*Wģ��RLC PDU SIZEͳ����Ϣ�ϱ��ظ�*/
    ID_WTTF_OM_RLC_PDU_SIZE_TRANS_INFO_IND      = 0xD008,    /*Wģ��RLC PDU SIZEͳ����Ϣ�ϱ�ָʾ*/
    ID_OM_WTTF_UPA_DATA_STATUS_G_INFO_REQ       = 0xD009,    /*Wģ��UPA Ҫ����ϢGֵ�ϱ�����*/
    ID_WTTF_OM_UPA_DATA_STATUS_G_INFO_CNF       = 0xD00a,    /*Wģ��UPA Ҫ����ϢGֵ�ϱ��ظ�*/
    ID_WTTF_OM_UPA_DATA_STATUS_G_INFO_IND       = 0xD00b,    /*Wģ��UPA Ҫ����ϢGֵ�ϱ�ָʾ*/
    ID_OM_TTF_MNTN_MSG_CTTF_OM_XXX_REQ          = 0xD00c,
    ID_OM_TTF_MNTN_MSG_CTTF_OM_YYY_REQ          = 0xD00d,
    ID_TTF_OM_MNTN_MSG_OM_CTTF_XXX_DATA_IND     = 0xD00e,
    ID_TTF_OM_MNTN_MSG_OM_CTTF_ZZZ_DATA_IND     = 0xD00f,

    /* Gģ��ά�ɲ���Ϣ�ı����D1��ͷ */
    ID_GRM_MNTN_OM_GRM_INFO_CFG_REQ             = 0xD104,   /*����GRM��Ϣ�۲⹦��*/
    ID_GRM_MNTN_GRM_OM_INFO_CFG_CNF             = 0xD105,
    ID_GRM_MNTN_GRM_OM_INFO                     = 0xD106,
    ID_GRM_MNTN_OM_GRM_THROUGHPUT_CFG_REQ       = 0xD107,   /*OM��GRM��������GRM������ͳ����Ϣ�۲⹦����Ϣ��*/
    ID_GRM_MNTN_GRM_OM_THROUGHPUT_CFG_CNF       = 0xD108,   /*GRM��OM�ظ�����GRM������ͳ����Ϣ�۲⹦����Ϣ��*/
    ID_GRM_MNTN_GRM_OM_THROUGHPUT_INFO          = 0xD109,   /*GRM��OM�ϱ�GRM������ͳ����Ϣ��Ϣ��*/
    ID_GRM_MNTN_OM_GTTF_ADV_TRACE_SWITCH_REQ    = 0xD10a,   /*Gģ��Trace �߼����ÿ�������*/
    ID_GRM_MNTN_GTTF_OM_ADV_TRACE_SWITCH_CNF    = 0xD10b,   /*Gģ��Trace �߼����ÿ��ػظ�*/

    /* RRM�Ŀ�ά�ɲ���Ϣ�ı����D2��ͷ */
    ID_RRM_OM_RESOURCE_STATE_INFO_IND           = 0xD210,    /* RRM�ϱ�����Դ״̬��Ϣ */

    /* AP�ϵ�TCPЭ��ջ�Ŀ�ά�ɲ���Ϣ, �����D3��ͷ */
    ID_OM_IPS_ADVANCED_TRACE_CONFIG_REQ         = 0xD313,   /* ����TCP/IPЭ��ջ ��������*/
    ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF         = 0xD314,   /* ����TCP/IPЭ��ջ ����ָʾ*/
    ID_OM_IPS_MNTN_INFO_CONFIG_REQ              = 0xD315,   /* �����Բ���TCP/IPЭ��ջ ������Ϣ����*/
    ID_IPS_OM_MNTN_INFO_CONFIG_CNF              = 0xD316,   /* �����Բ���TCP/IPЭ��ջ ������Ϣ����ָʾ*/
    ID_IPS_TRACE_INPUT_DATA_INFO                = 0xD317,               /*TCP/IP��ά�ɲ���ձ���*/
    ID_IPS_TRACE_OUTPUT_DATA_INFO               = 0xD318,               /*TCP/IP��ά�ɲⷢ�ͱ���*/
    ID_IPS_TRACE_BRIDGE_DATA_INFO               = 0xD319,               /*TCP/IP������ת����*/
    ID_IPS_TRACE_RECV_ARP_PKT                   = 0xD31A,               /*TCP/IPЭ��ջ���յ�ARP���Ʊ���*/
    ID_IPS_TRACE_SEND_ARP_PKT                   = 0xD31B,               /*TCP/IPЭ��ջ���͵�ARP���Ʊ���*/
    ID_IPS_TRACE_RECV_DHCPC_PKT                 = 0xD31C,               /*TCP/IPЭ��ջ���յ�DHCP���Ʊ���*/
    ID_IPS_TRACE_SEND_DHCPC_PKT                 = 0xD31D,               /*TCP/IPЭ��ջ���͵�DHCP���Ʊ���*/
    ID_IPS_TRACE_RECV_DHCPS_PKT                 = 0xD31E,               /*TCP/IPЭ��ջ���յ�DHCP���Ʊ���*/
    ID_IPS_TRACE_SEND_DHCPS_PKT                 = 0xD31F,               /*TCP/IPЭ��ջ���͵�DHCP���Ʊ���*/
    ID_IPS_TRACE_APP_CMD                        = 0xD320,               /*APP����������Ϣ*/
    ID_IPS_TRACE_MNTN_INFO                      = 0xD321,               /*TCP/IPЭ��ջ������Ϣ*/
    ID_IPS_TRACE_BRIDGE_PRE_ROUTING_INFO        = 0xD322,
    ID_IPS_TRACE_BRIDGE_POST_ROUTING_INFO       = 0xD323,
    ID_IPS_TRACE_BRIDGE_LOCAL_IN_INFO           = 0xD324,
    ID_IPS_TRACE_BRIDGE_LOCAL_OUT_INFO          = 0xD325,
    ID_IPS_TRACE_IP4_FORWARD_INFO               = 0xD326,
    ID_IPS_TRACE_IP4_LOCAL_IN_INFO              = 0xD327,
    ID_IPS_TRACE_IP4_LOCAL_OUT_INFO             = 0xD328,
    ID_IPS_TRACE_IP6_FORWARD_INFO               = 0xD329,
    ID_IPS_TRACE_IP6_LOCAL_IN_INFO              = 0xD32A,
    ID_IPS_TRACE_IP6_LOCAL_OUT_INFO             = 0xD32B,
    ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_START     = 0xD32C,
    ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_STOP      = 0xD32D,
    ID_IPS_TRACE_ADS_UL                         = 0xD330,
    ID_IPS_TRACE_ADS_DL                         = 0xD331,

    /* 1X�Ŀ�ά�ɲ���Ϣ�ı����D4��ͷ */
    ID_OM_CTTF_1X_MNTN_CONFIG_REQ               = 0xD400,   /* 1X ���ÿ�������, �����·����� */
    ID_CTTF_OM_1X_MNTN_CONFIG_CNF               = 0xD400,   /* 1X ���ÿ��ػظ�, ���ڻظ����ý�� */
    ID_CTTF_OM_1X_MNTN_FWD_LINK_IND             = 0xD402,   /* 1X Forward Link Info�ϱ� */
    ID_CTTF_OM_1X_MNTN_REV_LINK_IND             = 0xD403,   /* 1X Reverse Link Info�ϱ� */
    ID_CTTF_OM_1X_MNTN_RLP_STATISTICS_IND       = 0xD404,   /* 1X RLP statistics�ϱ� */
    ID_CTTF_OM_1X_MNTN_COMMON_CHANNEL_STATISTICS_IND       = 0xD405,   /* Common Channel statistics�ϱ� */

    /* CP�Ϲ���IP���ġ�PPP֮֡���ά�ⶼ����D5�� */
    /* CP�ϵ�TCPЭ��ջ�Ŀ�ά�ɲ���Ϣ, �����D51��ͷ
       ����IP���������ܱȽ϶�, ��Ԥ��һЩID�ռ�, D51~D55 */
    ID_OM_IPS_CCORE_ADVANCED_TRACE_CONFIG_REQ   = 0xD513,               /* ����TCP/IPЭ��ջ �������� */
    ID_IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF   = 0xD514,               /* ����TCP/IPЭ��ջ ����ָʾ */
    ID_OM_IPS_CCORE_MNTN_INFO_CONFIG_REQ        = 0xD515,               /* �����Բ���TCP/IPЭ��ջ ������Ϣ���� */
    ID_IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF        = 0xD516,               /* �����Բ���TCP/IPЭ��ջ ������Ϣ����ָʾ */
    ID_IPS_CCORE_TRACE_INPUT_DATA_INFO          = 0xD517,               /* TCP/IP��ά�ɲ���ձ��� */
    ID_IPS_CCORE_TRACE_OUTPUT_DATA_INFO         = 0xD518,               /* TCP/IP��ά�ɲⷢ�ͱ��� */
    ID_IPS_CCORE_TRACE_BRIDGE_DATA_INFO         = 0xD519,               /* TCP/IP������ת���� */
    ID_IPS_CCORE_TRACE_RECV_ARP_PKT             = 0xD51A,               /* TCP/IPЭ��ջ���յ�ARP���Ʊ��� */
    ID_IPS_CCORE_TRACE_SEND_ARP_PKT             = 0xD51B,               /* TCP/IPЭ��ջ���͵�ARP���Ʊ��� */
    ID_IPS_CCORE_TRACE_RECV_DHCPC_PKT           = 0xD51C,               /* TCP/IPЭ��ջ���յ�DHCP���Ʊ��� */
    ID_IPS_CCORE_TRACE_SEND_DHCPC_PKT           = 0xD51D,               /* TCP/IPЭ��ջ���͵�DHCP���Ʊ��� */
    ID_IPS_CCORE_TRACE_RECV_DHCPS_PKT           = 0xD51E,               /* TCP/IPЭ��ջ���յ�DHCP���Ʊ��� */
    ID_IPS_CCORE_TRACE_SEND_DHCPS_PKT           = 0xD51F,               /* TCP/IPЭ��ջ���͵�DHCP���Ʊ��� */
    ID_IPS_CCORE_TRACE_APP_CMD                  = 0xD520,               /* APP����������Ϣ */
    ID_IPS_CCORE_TRACE_MNTN_INFO                = 0xD521,               /* TCP/IPЭ��ջ������Ϣ */
    ID_IPS_MNTN_CCORE_IMS_NIC_INFO              = 0xD522,               /* IMS��������ͳ����Ϣ */
    ID_IPS_CCORE_TRACE_NIC_DATA_IND             = 0xD523,               /* TCP/IP��ά�ɲ���ձ��� */
    ID_IPS_CCORE_TRACE_NIC_DATA_REQ             = 0xD524,               /* TCP/IP��ά�ɲⷢ�ͱ��� */


    /* CP�ϵ�PPPC�Ŀ�ά�ɲ���Ϣ, �����D56��ͷ */
    ID_OM_PPP_MNTN_CONFIG_REQ                   = 0xD560,               /*PPP�յ�om������Ϣ*/
    ID_PPP_OM_MNTN_CONFIG_CNF                   = 0xD561,               /*PPPȷ���յ�om������Ϣ*/
    ID_PPP_OM_MNTN_STATISTIC_INFO               = 0xD562,               /*PPP����ά����Ϣ*/
    ID_OM_PPP_MNTN_TRACE_CONFIG_REQ         = 0xD563,               /* PPP�յ�OM ����������Ϣ*/


    ID_IMS_NIC_MNTN_TRACE_RCV_CONFIG_INFO       = 0xD5F1,
    ID_IMS_NIC_MNTN_TRACE_CONFIG_PROC_RSLT      = 0xD5F2,
    ID_IMS_NIC_MNTN_TRACE_RCV_CONFIG_DEL        = 0xD5F3,
    ID_IMS_NIC_MNTN_TRACE_RCV_CONFIG_DEL_RSLT   = 0xD5F4,
    ID_IMS_NIC_MNTN_TRACE_RUN_CMD               = 0xD5F5,
    ID_IMS_NIC_MNTN_TRACE_DNS_CFG               = 0xD5F6,
    ID_IMS_NIC_MNTN_TRACE_DNS_DEL               = 0xD5F7,
    ID_IMS_NIC_MNTN_TRACE_LOG_MSG               = 0xD5F8,
    ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG       = 0xD5F9,


    /* EVDO�Ŀ�ά�ɲ���Ϣ(��HRPD��eHRPD)�ı����D6��ͷ */
    ID_OM_CTTF_HRPD_MNTN_CONFIG_REQ                     = 0xD600,   /* HRPD ���ÿ�������, �����·����� */
    ID_CTTF_OM_HRPD_MNTN_CONFIG_CNF                     = 0xD601,   /* HRPD ���ÿ��ػظ�, ���ڻظ����ý�� */
    ID_CTTF_OM_HRPD_MNTN_MODULE_PROTOCOL_STATE_IND      = 0xD602,   /* HRPD Module Protocol State�ϱ� */
    ID_CTTF_OM_HRPD_MNTN_MAC_PROTOCOL_STATISTICS_IND    = 0xD603,   /* HRPD MAC Protocol Statistics�ϱ� */
    ID_CTTF_OM_HRPD_MNTN_RLP_STATISTICS_IND             = 0xD604,   /* HRPD RLP statistics�ϱ� */
    ID_CTTF_OM_HRPD_MNTN_MFPA_RLP_STATISTICS_IND        = 0xD605,   /* MFPA RLP statistics�ϱ� */
    ID_CTTF_OM_HRPD_MNTN_EMPA_RLP_STATISTICS_IND        = 0xD606,   /* EMPA RLP statistics�ϱ� */
    ID_CTTF_OM_HRPD_MNTN_REV_LINK_PACKET_INFO_IND       = 0xD607,   /* HRPD Reverse Link Packet Info�ϱ� */
    ID_CTTF_OM_HRPD_MNTN_REV_LINK_T2P_STATISTICS_IND    = 0xD608,   /* HRPD Reverse Link T2P statistics�ϱ� */
    ID_CTTF_OM_HRPD_MNTN_HARQ_INFO_IND                  = 0xD609,   /* HRPD Harq Info�ϱ� */
    ID_CTTF_OM_HRPD_MNTN_RTC3MAC_ACK_INFO_IND           = 0xD60A,   /* HRPD RTC3MAC Info�ϱ� */
    ID_CTTF_OM_HRPD_MNTN_TRACE_MSG_CONFIG_REQ           =0xD60B,    /* HRPD Trace Msg ������Ϣ*/

    TTF_MNTN_MSG_TYPE_BUTT                      = 0xFFFF
};
typedef VOS_UINT16 TTF_MNTN_MSG_TYPE_ENUM_UINT16;

enum TTF_MNTN_RPT_CMD_ENUM
{
    TTF_MNTN_RPT_CMD_STOP     = 0x00, /*ֹͣ�ϱ�*/
    TTF_MNTN_RPT_CMD_START    = 0x01  /*��ʼ�ϱ�*/
};
typedef VOS_UINT8 TTF_MNTN_RPT_CMD_ENUM_UINT8;

enum TTF_MNTN_RLP_RPT_CMD_ENUM
{
    TTF_MNTN_RLP_RPT_CMD_STOP   = 0x00, /*ֹͣ�ϱ�*/
    TTF_MNTN_RLP_RPT_CMD_START  = 0x01, /*��ʼ�ϱ�*/
    TTF_MNTN_RLP_RPT_CMD_CLEAR  = 0x02  /*���*/
};
typedef VOS_UINT8 TTF_MNTN_RLP_RPT_CMD_ENUM_UINT8;

enum TTF_MNTN_COMM_RPT_CMD_ENUM
{
    TTF_MNTN_COMM_RPT_CMD_STOP  = 0x00, /*ֹͣ�ϱ�*/
    TTF_MNTN_COMM_RPT_CMD_START = 0x01, /*��ʼ�ϱ�*/
    TTF_MNTN_COMM_RPT_CMD_CLEAR = 0x02  /*���*/
};
typedef VOS_UINT8 TTF_MNTN_COMM_RPT_CMD_ENUM_UINT8;

enum IPS_MNTN_INFO_ACTION_ENUM
{
    IPS_MNTN_INFO_REPORT_STOP           = 0,                    /*���������Բ���TCP/IPЭ��ջ������Ϣ*/
    IPS_MNTN_INFO_REPORT_START          = 1                     /*�ر������Բ���TCP/IPЭ��ջ������Ϣ*/
};
typedef VOS_UINT16 IPS_MNTN_INFO_ACTION_ENUM_UINT16;

enum IPS_MNTN_RESULT_TYPE_ENUM
{
    IPS_MNTN_RESULT_OK                  = 0,
    IPS_MNTN_RESULT_START_TIMER_FAIL    = 1,
    IPS_MNTN_RESULT_ALLOC_MEM_FAIL      = 2,
    IPS_MNTN_RESULT_ALLOC_MSG_FAIL      = 3,
    IPS_MNTN_RESULT_INPUT_PARAM_ERR     = 4,
    IPS_MNTN_RESULT_LOCAL_PARAM_ERR     = 5
};
typedef VOS_UINT32  IPS_MNTN_RESULT_TYPE_ENUM_UINT32;

enum GRM_MNTN_OM_REPORT_ACTION_ENUM
{
    GRM_MNTN_OM_REPORT_STOP     = 0,
    GRM_MNTN_OM_REPORT_START    = 1
};

typedef VOS_UINT16 GRM_MNTN_OM_REPORT_ACTION_ENUM_UINT16;

enum GRM_RESULT_TYPE_ENUM
{
    GRM_RESULT_OK                   = 0,
    GRM_RESULT_START_TIMER_FAIL     = 1,
    GRM_RESULT_ALLOC_MEM_FAIL       = 2,
    GRM_RESULT_ALLOC_MSG_FAIL       = 3,
    GRM_RESULT_INPUT_PARAM_ERR      = 4,
    GRM_RESULT_LOCAL_PARAM_ERR      = 5
};
typedef VOS_UINT32  GRM_RESULT_TYPE_ENUM_UINT32;

enum TOOL_GTTF_CFG_SWITCH_ENUM
{
    TOOL_GTTF_CFG_SWITCH_OFF = 0,
    TOOL_GTTF_CFG_SWITCH_ON  = 1
};
typedef VOS_UINT32 TOOL_GTTF_CFG_SWITCH_ENUM_UINT32;

enum GRM_TBF_INFO_TBF_MODE_ENUM
{
    Non_Extend_TBF = 0,
    Extend_TBF    = 1
};
typedef VOS_UINT8 GRM_TBF_INFO_TBF_MODE_ENUM_UINT8;

enum GRM_TBF_INFO_RLC_MODE_ENUM
{
    AM    = 0,  /* RLC AM mode*/
    UM    = 1   /* RLC UM mode*/
};
typedef VOS_UINT8 GRM_TBF_INFO_RLC_MODE_ENUM_UINT8;

enum GRM_TBF_INFO_COUNTDOWN_FLAG_ENUM
{
    No_Start_CV    = 0,
    Start_CV       = 1
};
typedef VOS_UINT8 GRM_TBF_INFO_COUNTDOWN_FLAG_ENUM_UINT8;

enum GRM_TBF_INFO_TI_ENUM
{
    TLLI_Absent           = 0,
    TLLI_Not_Absent       = 1
};
typedef VOS_UINT8 GRM_TBF_INFO_TI_ENUM_UINT8;

enum GRM_TBF_INFO_FINALBLKRXED_ENUM
{
    Not_received    = 0,  /* The Final Block the current TBF is not received. */
    Received        = 1   /* The Final Block the current TBF is received. */
};
typedef VOS_UINT8 GRM_TBF_INFO_FINALBLKRXED_ENUM_UINT8;

enum GRM_TBF_INFO_EDGE_CODE_SCHEME_ENUM
{
    CS_1       = 0x0000,
    CS_2       = 0x0001,
    CS_3       = 0x0002,
    CS_4       = 0x0003,
    MCS_1      = 0x1000,
    MCS_2      = 0x1001,
    MCS_3      = 0x1002,
    MCS_4      = 0x1003,
    MCS_5      = 0x1004,
    MCS_6      = 0x1005,
    MCS_7      = 0x1006,
    MCS_8      = 0x1007,
    MCS_9      = 0x1008,
    MCS_5_7    = 0x1009,
    MCS_6_9    = 0x100a
};
typedef VOS_UINT16 GRM_TBF_INFO_EDGE_CODE_SCHEME_ENUM_UINT16;

enum GRM_TBF_INFO_TEST_MODE_ENUM
{
    Test_Mode_A_Infinite      = 0, /*Aģʽ��PDU��������*/
    Test_Mode_A_Normal        = 1, /*Aģʽ��PDU��������*/
    Test_Mode_B               = 2, /*Bģʽ*/
    Test_Mode_SRB_LoopBack    = 3  /*EGPRS С����ģʽ*/
};
typedef VOS_UINT8 GRM_TBF_INFO_TEST_MODE_ENUM_UINT8;

enum GRM_TBF_INFO_TIMESLOT_FLAG_ENUM
{
    Not_Existed           = 0,  /* This TS is not existed */
    Existed               = 1   /* This TS is existed */
};
typedef VOS_UINT8 GRM_TBF_INFO_TIMESLOT_FLAG_ENUM_UINT8;

enum IPS_MNTN_CCORE_INFO_ACTION_ENUM
{
    IPS_MNTN_CCORE_INFO_REPORT_STOP           = 0,                    /*���������Բ���TCP/IPЭ��ջ������Ϣ*/
    IPS_MNTN_CCORE_INFO_REPORT_START          = 1                     /*�ر������Բ���TCP/IPЭ��ջ������Ϣ*/
};
typedef VOS_UINT16 IPS_MNTN_CCORE_INFO_ACTION_ENUM_UINT16;

enum IPS_MNTN_CCORE_RESULT_TYPE_ENUM
{
    IPS_MNTN_CCORE_RESULT_OK                  = 0,
    IPS_MNTN_CCORE_RESULT_START_TIMER_FAIL    = 1,
    IPS_MNTN_CCORE_RESULT_ALLOC_MEM_FAIL      = 2,
    IPS_MNTN_CCORE_RESULT_ALLOC_MSG_FAIL      = 3,
    IPS_MNTN_CCORE_RESULT_INPUT_PARAM_ERR     = 4,
    IPS_MNTN_CCORE_RESULT_LOCAL_PARAM_ERR     = 5
};
typedef VOS_UINT32  IPS_MNTN_CCORE_RESULT_TYPE_ENUM_UINT32;

enum WTTF_TRACE_PHY_MAC_SUB_ATTRIB_ENUM     /*���ڱ�ʶPHY-->MAC   ID_WTTF_PHY_MAC_DATA_IND
                                                  MAC-->PHY  ID_WTTF_MAC_PHY_DATA_REQ*/
{
    WTTF_TRACE_PHY_MAC_NULL = 0,
    WTTF_TRACE_CTRL_HEADER  = 1,
    WTTF_TRACE_WHOLE_DATA   = 2
};
typedef VOS_UINT8   WTTF_TRACE_PHY_MAC_SUB_ATTRIB_ENUM_UINT8;

enum WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM
{
    WTTF_TRACE_MSG_NO   = 0,
    WTTF_TRACE_MSG_YES  = 1
};
typedef VOS_UINT8   WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8;

enum IPS_MNTN_CCORE_TRACE_CHOSEN_ENUM
{
    IPS_MNTN_CCORE_TRACE_NULL_CHOSEN               =   0,             /*����������Ϣ*/
    IPS_MNTN_CCORE_TRACE_MSG_HEADER_CHOSEN         =   1,             /*������ͷ��*/
    IPS_MNTN_CCORE_TRACE_CONFIGURABLE_LEN_CHOSEN   =   2,             /*�������ò�����*/
    IPS_MNTN_CCORE_TRACE_WHOLE_DATA_LEN_CHOSEN     =   3              /*������ȫ������*/
};
typedef VOS_UINT32   IPS_MNTN_CCORE_TRACE_CHOSEN_ENUM_UINT32;

enum IPS_MNTN_TRACE_CHOSEN_ENUM
{
    IPS_MNTN_TRACE_NULL_CHOSEN               =   0,             /*����������Ϣ*/
    IPS_MNTN_TRACE_MSG_HEADER_CHOSEN         =   1,             /*������ͷ��*/
    IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN   =   2,             /*�������ò�����*/
    IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN     =   3              /*������ȫ������*/
};
typedef VOS_UINT32   IPS_MNTN_TRACE_CHOSEN_ENUM_UINT32;

enum TTF_MNTN_TRACE_CHOSEN_ENUM
{
    TTF_MNTN_TRACE_NULL_CHOSEN               =   0,             /*����������Ϣ*/
    TTF_MNTN_TRACE_MSG_HEADER_CHOSEN         =   1,             /*������ͷ��*/
    TTF_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN   =   2,             /*�������ò�����*/
    TTF_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN     =   3              /*������ȫ������*/
};
typedef VOS_UINT32   TTF_MNTN_TRACE_CHOSEN_ENUM_UINT32;

enum WTTF_RLC_MNTN_RB_CHOSEN_ENUM
{
    WTTF_RLC_MNTN_RB_NULL_CHOSEN                = 0x0,                  /* ȡ������ */
    WTTF_RLC_MNTN_RB_SIGNALLING_CHOSEN          = 0x0000000F,           /* ����RB */
    WTTF_RLC_MNTN_RB_PS_CHOSEN                  = 0xFFFFFFF0,           /* ҵ��RB */
    WTTF_RLC_MNTN_RB_ALL_CHOSEN                 = 0xFFFFFFFF            /* ALL RB */
};
typedef VOS_UINT32   WTTF_RLC_MNTN_RB_CHOSEN_ENUM_UINT32;

/* HIDS����, Ҫ��ÿ��ö��ֵ��������ʾ������ֵ, �����ܽ��� */
enum CTTF_1X_MAC_MNTN_RATE_ENUM
{
    CTTF_1X_MAC_MNTN_RATE_BLANK    = 0,
    CTTF_1X_MAC_MNTN_RATE_EIGHTH    = 1,
    CTTF_1X_MAC_MNTN_RATE_QUARTER  = 2,
    CTTF_1X_MAC_MNTN_RATE_HALF      = 3,
    CTTF_1X_MAC_MNTN_RATE_FULL      = 4,
    CTTF_1X_MAC_MNTN_RATE_2X        = 5,
    CTTF_1X_MAC_MNTN_RATE_4X        = 6,
    CTTF_1X_MAC_MNTN_RATE_8X        = 7,
    CTTF_1X_MAC_MNTN_RATE_16X       = 8,
    CTTF_1X_MAC_MNTN_RATE_32X       = 9,
    CTTF_1X_MAC_MNTN_RATE_BUTT     = 10
};
typedef VOS_UINT8 CTTF_1X_MAC_MNTN_RATE_ENUM_UINT8;

enum CTTF_1X_MAC_MNTN_RESULT_TYPE_ENUM
{
    CTTF_1X_MAC_MNTN_RESULT_OK                  = 0,
    CTTF_1X_MAC_MNTN_RESULT_START_TIMER_FAIL    = 1,
    CTTF_1X_MAC_MNTN_RESULT_ALLOC_MEM_FAIL      = 2,
    CTTF_1X_MAC_MNTN_RESULT_ALLOC_MSG_FAIL      = 3,
    CTTF_1X_MAC_MNTN_RESULT_INPUT_PARAM_ERR     = 4,
    CTTF_1X_MAC_MNTN_RESULT_LOCAL_PARAM_ERR     = 5
};
typedef VOS_UINT32 CTTF_1X_MAC_MNTN_RESULT_TYPE_ENUM_UINT32;

enum CTTF_1X_MAC_MNTN_RPT_PERIOD_ENUM
{
    CTTF_1X_MAC_MNTN_RPT_PERIOD_1280          = 1280,                    /* �ϱ�����1280ms */
};
typedef VOS_UINT32 CTTF_1X_MAC_MNTN_RPT_PERIOD_ENUM_UINT32;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_RPT_PERIOD_ENUM_UINT32
 * Description : hrpd�ϱ����
*******************************************************************************/
enum CTTF_HRPD_MNTN_RESULT_TYPE_ENUM
{
    CTTF_HRPD_MNTN_RESULT_OK                  = 0,
    CTTF_HRPD_MNTN_RESULT_START_TIMER_FAIL    = 1,
    CTTF_HRPD_MNTN_RESULT_ALLOC_MEM_FAIL      = 2,
    CTTF_HRPD_MNTN_RESULT_ALLOC_MSG_FAIL      = 3,
    CTTF_HRPD_MNTN_RESULT_INPUT_PARAM_ERR     = 4,
    CTTF_HRPD_MNTN_RESULT_LOCAL_PARAM_ERR     = 5
};
typedef VOS_UINT32 CTTF_HRPD_MNTN_RESULT_TYPE_ENUM_UINT32;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_RPT_PERIOD_ENUM_UINT32
 * Description : hrpd�ϱ�����
*******************************************************************************/
enum CTTF_HRPD_MNTN_RPT_PERIOD_ENUM
{
    CTTF_HRPD_MNTN_RPT_PERIOD_1280              = 1280                          /* �ϱ�����1280ms */
};

typedef VOS_UINT32 CTTF_HRPD_MNTN_RPT_PERIOD_ENUM_UINT32;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_RTC_RPT_PERIOD_ENUM_UINT32
 * Description : hrpd RTC ��ͼ�ϱ�����
*******************************************************************************/
enum CTTF_HRPD_MNTN_RTC_RPT_PERIOD_ENUM
{
    CTTF_HRPD_MNTN_RTC_RPT_PERIOD_640           = 640                           /* �ϱ�����640ms */
};
typedef VOS_UINT32 CTTF_HRPD_MNTN_RTC_RPT_PERIOD_ENUM_UINT32;


/*����VISP��־������ȼ�*/
enum IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_E_ENUM
{
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_CRITICAL = 0,
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_ERROR,
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_WARNING,
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_INFO,
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_DEBUG,

    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_BUIT
};
typedef VOS_UINT8 IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_E_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM
 * Description : HRPD��Э������
*******************************************************************************/
enum CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM
{
    CTTF_HRPD_MNTN_DEFAULT_CC_MAC_ENUM                      = 0x00,
    CTTF_HRPD_MNTN_ENHANCE_CC_MAC_ENUM                      = 0x01,
    CTTF_HRPD_MNTN_DEFAULT_AC_MAC_ENUM                      = 0x02,
    CTTF_HRPD_MNTN_ENHANCE_AC_MAC_ENUM                      = 0x03,
    CTTF_HRPD_MNTN_DEFAULT_FTC_MAC_ENUM                     = 0x04,
    CTTF_HRPD_MNTN_ENHANCE_FTC_MAC_ENUM                     = 0x05,
    CTTF_HRPD_MNTN_DEFAULT_RTC_MAC_ENUM                     = 0x06,
    CTTF_HRPD_MNTN_SUBTYPE3_RTC_MAC_ENUM                    = 0x07,
    CTTF_HRPD_MNTN_DEFAULT_AUTHENTICATION_ENUM              = 0x08,
    CTTF_HRPD_MNTN_SHA1_AUTHENTICATION_ENUM                 = 0x09,
    CTTF_HRPD_MNTN_DEFAULT_ENCRYPTION_ENUM                  = 0x0a,
    CTTF_HRPD_MNTN_AES_ENCRYPTION_ENUM                      = 0x0b,
    CTTF_HRPD_MNTN_DEFAULT_SECURITY_ENUM                    = 0x0c,
    CTTF_HRPD_MNTN_GENERIC_SECURITY_ENUM                    = 0x0d,
    CTTF_HRPD_MNTN_DEFAULT_STREAM_ENUM                      = 0x0e,
    CTTF_HRPD_MNTN_DEFAULT_SIGNALING_APP_ENUM               = 0x0f,
    CTTF_HRPD_MNTN_DEFAULT_PACKET_APP_RN_ENUM               = 0x10,
    CTTF_HRPD_MNTN_DEFAULT_PACKET_APP_SN_ENUM               = 0x11,
    CTTF_HRPD_MNTN_TEST_APP_ENUM                            = 0x12,
    CTTF_HRPD_MNTN_MULTI_FLOW_PACKET_APP_RN_ENUM            = 0x13,
    CTTF_HRPD_MNTN_MULTI_FLOW_PACKET_APP_SN_ENUM            = 0x14,
    CTTF_HRPD_MNTN_3G1X_CIRCUIT_SERVICE_NOTIFICATION_APP_ENUM   = 0x15,
    CTTF_HRPD_MNTN_RESERVED_APP_ENUM                        = 0x16,
    CTTF_HRPD_MNTN_ENHANCED_MULTI_FLOW_PACKET_APP_RN_ENUM   = 0x17,
    CTTF_HRPD_MNTN_ENHANCED_MULTI_FLOW_PACKET_APP_SN_ENUM   = 0x18,
    CTTF_HRPD_MNTN_ENHANCED_TEST_APP_ENUM                   = 0x19,
    CTTF_HRPD_MNTN_STREAM_NOT_USED_ENUM                     = 0x1a,
    CTTF_HRPD_MNTN_NO_SUB_PROTOCOL_ENUM                     = 0x1b,
    CTTF_HRPD_MNTN_SUB_PROTOCOL_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MAC_TRANS_MODE_ENUM_UINT8
 * Description : ����ģʽ
*******************************************************************************/
enum CTTF_HRPD_MAC_TRANS_MODE_ENUM
{
    CTTF_HRPD_MAC_TRANS_MODE_HIGH_CAPACITY  = 0x00,
    CTTF_HRPD_MAC_TRANS_MODE_LOW_LATENCY    = 0x01,
    CTTF_HRPD_MAC_TRANS_MODE_BUTT           = 0x02
};
typedef VOS_UINT8 CTTF_HRPD_MAC_TRANS_MODE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : CSDR_HRPD_MNTN_SUBPACKET_TYPE_ENUM_UINT16
 *
 * Description : It's used to define subpacketID, it means how many times the
 * packet is sent.
 *******************************************************************************/
enum CSDR_HRPD_MNTN_SUBPACKET_TYPE_ENUM
{
    CSDR_HARQ_MNTN_SUBPACKET_FIRST_TIME      = 0x0000,
    CSDR_HARQ_MNTN_SUBPACKET_SECOND_TIME     = 0x0001,
    CSDR_HARQ_MNTN_SUBPACKET_THIRD_TIME      = 0x0002,
    CSDR_HARQ_MNTN_SUBPACKET_FOURTH_TIME     = 0x0003,
    CSDR_HARQ_MNTN_SUBPACKET_BUTT            = 0x0004
};
typedef VOS_UINT16 CSDR_HRPD_MNTN_SUBPACKET_TYPE_ENUM_UINT16;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_RTC3MAC_WORK_MODE_ENUM_UINT8
 * Description : T2P����ģʽ
*******************************************************************************/
enum CTTF_HRPD_MNTN_RTC3MAC_WORK_MODE_ENUM
{
    CTTF_HRPD_MNTN_RTC3MAC_MODE_NORMAL                  = 0x00, /* ͨ��ģʽ */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_PHY_FORBIDDEN           = 0x01, /* PHY��ֹ���� */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_SUPERVISION_FAILED      = 0x02, /* supervision failed֮��������ʧȥ��ϵ */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_SILENCE_DURATION        = 0x03, /* ��Ĭ */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_TEST_LOOP               = 0x04, /* ����ģʽ */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_PREEMPT                 = 0x05, /* ����ռ */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_RTC_SETUP_STATUS        = 0x06, /* RTC3����setup״̬ */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_ATTR_PARA_CHANGE_NEGO   = 0x07, /* ��Э�̸ı�Э�̲��� */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_ATTR_PARA_CHANGE_GAUP   = 0x08, /* GAUP�ı�Э�̲��� */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_TCH_PARA_CHANGE         = 0x09, /* TCH�����ı� */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_OTHER                   = 0x0A, /* ���� */
    CTTF_HRPD_MNTN_RTC3MAC_WORK_MODE_BUTT               = 0x0B
};
typedef VOS_UINT8 CTTF_HRPD_MNTN_RTC3MAC_WORK_MODE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_CC_STATE_ENUM
 * Description : DCC��ECC��״̬,���չ��ߵ�Ҫ��, DCC��ECC��״̬Ҫ������һ��
*******************************************************************************/
enum CTTF_HRPD_MNTN_CC_STATE_ENUM
{
    CTTF_HRPD_MNTN_CC_INACTIVE_STATE    = 0x0,
    CTTF_HRPD_MNTN_CC_ACTIVE_STATE      = 0x1,
    CTTF_HRPD_MNTN_CC_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_CC_STATE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_CC_STATE_ENUM
 * Description : SDAC��EAC��״̬,���չ��ߵ�Ҫ��, DAC��EAC��״̬Ҫ������һ��
*******************************************************************************/
enum CTTF_HRPD_MNTN_AC_STATE_ENUM
{
    CTTF_HRPD_MNTN_AC_INACTIVE_STATE    = 0x0,
    CTTF_HRPD_MNTN_AC_ACTIVE_STATE      = 0x1,
    CTTF_HRPD_MNTN_AC_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_AC_STATE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_FTC_STATE_ENUM
 * Description : DFTC��EFTC��״̬,���չ��ߵ�Ҫ��, DFTC��EFTC��״̬Ҫ������һ��
*******************************************************************************/
enum CTTF_HRPD_MNTN_FTC_STATE_ENUM
{
    CTTF_HRPD_MNTN_FTC_INACTIVE_STATE       = 0x0,
    CTTF_HRPD_MNTN_FTC_VARIABLE_RATE_STATE  = 0x1,
    CTTF_HRPD_MNTN_FTC_FIXED_RATE_STATE     = 0x2,
    CTTF_HRPD_MNTN_FTC_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_FTC_STATE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_RTC_STATE_ENUM
 * Description : DRTC��ST3 RTC��״̬,���չ��ߵ�Ҫ��, DRTC��ST3 RTC��״̬Ҫ������һ��
*******************************************************************************/
enum CTTF_HRPD_MNTN_RTC_STATE_ENUM
{
    CTTF_HRPD_MNTN_RTC_INACTIVE_STATE   = 0x0,
    CTTF_HRPD_MNTN_RTC_SETUP_STATE      = 0x1,
    CTTF_HRPD_MNTN_RTC_OPEN_STATE       = 0x2,
    CTTF_HRPD_MNTN_RTC_SUSPENDED_STATE  = 0x3,
    CTTF_HRPD_MNTN_RTC_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_RTC_STATE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_ENUM
 * Description : ��ȫ��Э��״̬
*******************************************************************************/
enum CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_ENUM
{
    CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_NO_STATE     = 0x0,
    CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_PROTOCOL_STATE_ENUM
 * Description : ���ز�Э��״̬
*******************************************************************************/
enum CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_PROTOCOL_STATE_ENUM
{
    CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_CLOSE_STATE         = 0x0,
    CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_OPEN_STATE          = 0x1,
    CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_PROTOCOL_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_PROTOCOL_STATE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_STREAM_APP_PROTOCOL_STATE_ENUM
 * Description : ��Ӧ�ò�Э��״̬
                 ����Ҫ��Default Packet Application, Multi-flow Packet Application,
                 Enhanced Multi-flow Packet Application, Data Over Signalling,
                 Test Application, �Լ�Enhanced Test Application������һ��
*******************************************************************************/
enum CTTF_HRPD_MNTN_STREAM_APP_PROTOCOL_STATE_ENUM
{
    CTTF_HRPD_MNTN_STREAM_APP_RESERVATION_CLOSE_STATE   = 0x0,
    CTTF_HRPD_MNTN_STREAM_APP_RESERVATION_STATE         = 0x1,
    CTTF_HRPD_MNTN_STREAM_APP_NO_STATE                  = 0x2,
    CTTF_HRPD_MNTN_STREAM_APP_PROTOCOL_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_STREAM_APP_PROTOCOL_STATE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_SNP_UP_TX_STATE_ENUM
 * Description : SNPЭ��״̬
*******************************************************************************/
enum CTTF_HRPD_MNTN_SNP_UP_TX_STATE_ENUM
{
    CTTF_HRPD_MNTN_SNP_UP_TX_ALLOW_STATE                = 0x0,
    CTTF_HRPD_MNTN_SNP_UP_TX_NOT_ALLOW_STATE            = 0x1,
    CTTF_HRPD_MNTN_SNP_UP_TX_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_SNP_UP_TX_STATE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_RTCMAC_MNTN_RATE_ENUM_UINT8
 * Description : Default RTC ��������ö��
*******************************************************************************/
enum CTTF_HRPD_RTCMAC_MNTN_RATE_ENUM
{
    CTTF_HRPD_RTCMAC_MNTN_RATE_NULL              = 0,
    CTTF_HRPD_RTCMAC_MNTN_RATE_9K6               = 1,
    CTTF_HRPD_RTCMAC_MNTN_RATE_19K2              = 2,
    CTTF_HRPD_RTCMAC_MNTN_RATE_38K4              = 3,
    CTTF_HRPD_RTCMAC_MNTN_RATE_76K8              = 4,
    CTTF_HRPD_RTCMAC_MNTN_RATE_153K6             = 5,
    CTTF_HRPD_RTCMAC_MNTN_RATE_NO_LIMITATION     = 6,   /* ��ʾ��Rate������ */
    CTTF_HRPD_RTCMAC_MNTN_RATE_BUTT              = 7    /* ��ʾ��Ч */
};
typedef VOS_UINT8 CTTF_HRPD_RTCMAC_MNTN_RATE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��     :  PPP_MNTN_OM_RESULT_TYPE_ENUM_UINT8
 ˵��:     pppά����Ϣ֪ͨ���
*****************************************************************************/
enum PPP_MNTN_OM_RESULT_TYPE_ENUM
{
    PPP_MNTN_OM_RESULT_OK                  = 0,
    PPP_MNTN_OM_RESULT_INPUT_PARAM_ERR     = 1,
    PPP_MNTN_OM_RESULT_BUTT
};
typedef VOS_UINT8 PPP_MNTN_OM_RESULT_TYPE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_PA_MNTN_FLOW_PROTOCOL_ENUM_UINT8
 * Description : Flow Protocol Identifier
                 C.R1001-H_v1.0_Administration of Parameter Value Assignments for cdma2000
                 Spread Spectrum Standards Table 11.3-1
*******************************************************************************/
enum CTTF_HRPD_PA_MNTN_FLOW_PROTOCOL_ENUM
{
    CTTF_HRPD_PA_MNTN_FLOW_PROTOCOL_NULL                            = 0x00,
    CTTF_HRPD_PA_MNTN_HDLC_LIKE_FRMAING_WITH_PPP                    = 0x01,
    CTTF_HRPD_PA_MNTN_IPV4                                          = 0x02,
    CTTF_HRPD_PA_MNTN_IPV6                                          = 0x03,
    CTTF_HRPD_PA_MNTN_ROHC                                          = 0x04,
    CTTF_HRPD_PA_MNTN_IPV4_AND_IPV6                                 = 0x05,
    CTTF_HRPD_PA_MNTN_HDLC_LIKE_FRMAING_WITH_ALTPPP                 = 0x06,
    CTTF_HRPD_PA_MNTN_HDLC_LIKE_FRMAING_SUPPORTING_MULTIPLE_PDNS    = 0x07,
    CTTF_HRPD_PA_MNTN_PDN_MUX_FOR_IP_PDNS                           = 0x08,
    CTTF_HRPD_PA_MNTN_BCMCS_OVER_UNICAST_WITH_HDLC_LIKE_FRAMING     = 0x09,
    CTTF_HRPD_PA_MNTN_BCMCS_OVER_UNICAST_WITH_SEG_BASED_FRAMING     = 0x0A,
    CTTF_HRPD_PA_MNTN_FLOW_PROTOCOL_BUTT
};
typedef VOS_UINT8 CTTF_HRPD_PA_MNTN_FLOW_PROTOCOL_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_ENUM_UINT8
 * Description : Route Protocol Identifier
                 C.R1001-H_v1.0_Administration of Parameter Value Assignments for cdma2000
                 Spread Spectrum Standards Table 11.3-1
*******************************************************************************/
enum CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_ENUM
{
    CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_NULL                           = 0x00,
    CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_ROHC                           = 0x04,
    CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_BUTT
};
typedef VOS_UINT8 CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_ENUM_UINT8;

/*****************************************************************************
 ö����    : CTTF_HRPD_MNTN_RTC3MAC_PAKETSIZE_INDEX_ENUM_UINT8
 ö��˵��  : �����֧�ֵ�PacketSize����
*****************************************************************************/
enum CTTF_HRPD_MNTN_RTC3MAC_PAKETSIZE_INDEX_ENUM
{
    CTTF_HRPD_MNTN_RTC3MAC_PS_0         = 0x00,  /* PS��СΪ0bit<-->0Byte */
    CTTF_HRPD_MNTN_RTC3MAC_PS_128       = 0x01,  /* PS��СΪ128bit<-->16BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_256       = 0x02,  /* PS��СΪ256bit<-->32BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_512       = 0x03,  /* PS��СΪ512bit<-->64BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_768       = 0x04,  /* PS��СΪ768bit<-->96BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_1024      = 0x05,  /* PS��СΪ1024bit<-->128BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_1536      = 0x06,  /* PS��СΪ1536bit<-->192BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_2048      = 0x07,  /* PS��СΪ2048bit<-->256BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_3072      = 0x08,  /* PS��СΪ3072bit<-->384BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_4096      = 0x09,  /* PS��СΪ4096bit<-->512BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_6144      = 0x0A,  /* PS��СΪ6144bit<-->768BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_8192      = 0x0B,  /* PS��СΪ8192bit<-->1024BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_12288     = 0x0C,  /* PS��СΪ12288bit<-->1536BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_BUTT      = 0x0D
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_RTC3MAC_PAKETSIZE_INDEX_ENUM_UINT8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
/* R99 Mailbox VTB �������ݵ�ַ */
extern VOS_UINT32  g_aulR99MailboxVtbAddr[];


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT32  ulMsgId;

    VOS_UINT16  usOriginalId;
    VOS_UINT16  usTerminalId;
    VOS_UINT32  ulTimeStamp;
    VOS_UINT32  ulSN;
}DIAG_TRANS_MSG_HDR_STRU;

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
   Wģ��ά�ɲ���Ϣ
*****************************************************************************/
typedef struct
{
    WTTF_RLC_MNTN_RB_CHOSEN_ENUM_UINT32     enConfig;       /* ��32bit,�ӵ͵��߷ֱ����RB1~RB32,RB0Ĭ�Ϲ�ȡ  */
                                                            /* ����RB: 0x000F */
                                                            /* ҵ��RB: 0xFFF0 */
                                                            /* ALL RB: 0xFFFF */
                                                            /* ȡ������: 0x0000 */
    VOS_UINT16                              usTracePduSize;
    VOS_UINT16                              usTraceCipherPduSize;
    VOS_UINT16                              usTracePduCnt;
    VOS_UINT8                               aucRsv[2];
}WTTF_TRACE_MAC_RLC_DATA_IND_CONFIG_STRU;
typedef WTTF_TRACE_MAC_RLC_DATA_IND_CONFIG_STRU WTTF_TRACE_RLC_MAC_DATA_REQ_CONFIG_STRU;

typedef struct
{
    WTTF_TRACE_PHY_MAC_SUB_ATTRIB_ENUM_UINT8    enConfig;
    VOS_UINT8                                   aucRsv[3];
}WTTF_TRACE_PHY_MAC_DATA_IND_CONFIG_STRU;

typedef WTTF_TRACE_PHY_MAC_DATA_IND_CONFIG_STRU  WTTF_TRACE_MAC_PHY_DATA_REQ_CONFIG_STRU;
typedef WTTF_TRACE_PHY_MAC_DATA_IND_CONFIG_STRU  WTTF_TRACE_PHY_MAC_HS_PDU_DATA_IND_CONFIG_STRU;
typedef WTTF_TRACE_PHY_MAC_DATA_IND_CONFIG_STRU  WTTF_TRACE_UPA_PHY_DATA_REQ_CONFIG_STRU;

typedef struct
{
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8     enConfig;
    VOS_UINT8                                   aucRsv[3];
}WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU;

typedef struct
{
    TTF_MNTN_TRACE_CHOSEN_ENUM_UINT32           enChoice;
    VOS_UINT32                                  ulTraceDataLen;              /* ��ѡ��TTF_MNTN_TRACE_CONFIGURABLE_LEN_CHOSENʱ����ֵ��Ч */
}TTF_MNTN_TRACE_DATA_CONFIG_STRU;

typedef TTF_MNTN_TRACE_DATA_CONFIG_STRU WTTF_TRACE_PDCP_RABM_DATA_IND_CONFIG_STRU;
typedef TTF_MNTN_TRACE_DATA_CONFIG_STRU WTTF_TRACE_RABM_PDCP_DATA_REQ_CONFIG_STRU;

typedef struct
{
    IPS_MNTN_TRACE_CHOSEN_ENUM_UINT32   ulChoice;
    VOS_UINT32                          ulTraceDataLen;         /* ��ѡ��TRACE_CONFIGURABLE_LEN_CHOSENʱ����ֵ��Ч */
}IPS_MNTN_TRACE_CONFIG_STRU;

typedef IPS_MNTN_TRACE_CONFIG_STRU  IPS_MNTN_BRIDGE_TRACE_CFG_STRU;
typedef IPS_MNTN_TRACE_CONFIG_STRU  IPS_MNTN_INPUT_TRACE_CFG_STRU;
typedef IPS_MNTN_TRACE_CONFIG_STRU  IPS_MNTN_OUTPUT_TRACE_CFG_STRU;
typedef IPS_MNTN_TRACE_CONFIG_STRU  IPS_MNTN_LOCAL_TRACE_CFG_STRU;

typedef struct
{
    IPS_MNTN_CCORE_TRACE_CHOSEN_ENUM_UINT32   ulChoice;
    VOS_UINT32                                ulTraceDataLen;         /* ��ѡ��TRACE_CONFIGURABLE_LEN_CHOSENʱ����ֵ��Ч */
}IPS_MNTN_CCORE_TRACE_CONFIG_STRU;

typedef IPS_MNTN_CCORE_TRACE_CONFIG_STRU  IPS_MNTN_CCORE_BRIDGE_TRACE_CFG_STRU;
typedef IPS_MNTN_CCORE_TRACE_CONFIG_STRU  IPS_MNTN_CCORE_INPUT_TRACE_CFG_STRU;
typedef IPS_MNTN_CCORE_TRACE_CONFIG_STRU  IPS_MNTN_CCORE_OUTPUT_TRACE_CFG_STRU;


/*****************************************************************************
 �ṹ��     : OM_TTF_WCDMA_RLC_DATA_TRANS_INFO_REQ_STRU
 ��Ӧ��Ϣ: ID_OM_WTTF_RLC_DATA_TRANS_INFO_REQ
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                     stTransHdr;
    TTF_MNTN_RPT_CMD_ENUM_UINT8                 enCommand;        /*��ʼ��ֹͣ�ϱ�*/
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8     enRptAM;
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8     enRptUM;
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8     enRptTM;
    VOS_UINT32                                  ulRptPeriod;      /*��1..5����λ����,��������*/
} OM_TTF_WCDMA_RLC_DATA_TRANS_INFO_REQ_STRU;


/*****************************************************************************
 �ṹ��     : TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_CNF_STRU
 ��Ӧ��Ϣ: ID_WTTF_OM_RLC_DATA_TRANS_INFO_CNF
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    PS_RSLT_CODE_ENUM_UINT32          enRslt;         /* ���ز�ѯ�ṹ�ɹ���ʧ�� */
} TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_CNF_STRU;

typedef TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_CNF_STRU TTF_OM_RLC_PDU_SIZE_TRANS_INFO_CNF_STRU;
typedef TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_CNF_STRU TTF_OM_UPA_DATA_STATUS_G_INFO_CNF_STRU;

/*****************************************************************************
 �ṹ��     : WTTF_TRACE_MSG_CONFIG_STRU
 ��Ӧ��Ϣ: WTTF_TRACE_MSG_CONFIG_STRU
*****************************************************************************/
typedef struct
{
    WTTF_TRACE_MAC_RLC_DATA_IND_CONFIG_STRU         stTraceMacRlcDataIndCfg;
    WTTF_TRACE_RLC_MAC_DATA_REQ_CONFIG_STRU         stTraceRlcMacDataReqCfg;

    WTTF_TRACE_PHY_MAC_DATA_IND_CONFIG_STRU         stTracePhyMacDataIndCfg;
    WTTF_TRACE_MAC_PHY_DATA_REQ_CONFIG_STRU         stTraceMacPhyDataReqCfg;

    WTTF_TRACE_PHY_MAC_HS_PDU_DATA_IND_CONFIG_STRU  stTracePhyMacHsPduDataIndCfg;
    WTTF_TRACE_UPA_PHY_DATA_REQ_CONFIG_STRU         stTraceUpaPhyDataReqCfg;

    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTracePhyMacInfoIndCfg;
    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTraceUpaStatusIndCfg;
    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTraceUpaSchedStausIndCfg;

    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTraceMacPhyAmrDataIndCfg;
    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTracePhyRlcAmrDataReqCfg;

    WTTF_TRACE_PDCP_RABM_DATA_IND_CONFIG_STRU       stTracePdcpRabmDataIndCfg;
    WTTF_TRACE_RABM_PDCP_DATA_REQ_CONFIG_STRU       stTraceRabmPdcpDataReqCfg;

    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTraceRlcMacIPDataCfg;
    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTraceMacRlcIPDataCfg;
}WTTF_TRACE_MSG_CONFIG_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    WTTF_TRACE_MSG_CONFIG_STRU        stAdvancedConfig;
}OM_TTF_WCDMA_ADVANCED_TRACE_CONFIG_REQ_STRU;


/*****************************************************************************
 �ṹ��     : TTF_OM_WCDMA_ADVANCED_TRACE_CONFIG_CNF_STRU
 ��Ӧ��Ϣ: ID_WTTF_OM_ADVANCED_TRACE_CONFIG_CNF
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    PS_RSLT_CODE_ENUM_UINT32          enRslt;         /* ���ز�ѯ�ṹ�ɹ���ʧ�� */

} TTF_OM_WCDMA_ADVANCED_TRACE_CONFIG_CNF_STRU;


/*****************************************************************************
 �ṹ��     :  OM_TTF_WCDMA_RLC_PDU_SIZE_TRANS_INFO_REQ_STRU
 ��Ӧ��Ϣ:  ID_OM_WTTF_RLC_PDU_SIZE_TRANS_INFO_REQ
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU             stTransHdr;
    TTF_MNTN_RPT_CMD_ENUM_UINT8         enCommand;        /*��ʼ��ֹͣ�ϱ�*/
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulRptPeriod;    /*��1..5����λ����,��������*/
} OM_TTF_WCDMA_RLC_PDU_SIZE_TRANS_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��     :  WTTF_MNTN_RLC_PDU_SIZE_INFO_STRU
 ��Ӧ��Ϣ:  WTTF_MNTN_RLC_PDU_SIZE_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPduSize;
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulPduCount;
}WTTF_MNTN_RLC_PDU_SIZE_INFO_STRU;

/*****************************************************************************
 �ṹ��     :  TTF_OM_WCDMA_RLC_PDU_SIZE_TRANS_INFO_STRU
 ��Ӧ��Ϣ:  TTF_OM_WCDMA_RLC_PDU_SIZE_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRbId;
    PS_BOOL_ENUM_UINT8                  enExist;                  /*PS_TRUE:��ʾ��RbId���ڲ���֧��RLC PDU SIZE�ɱ䡣*/
    VOS_UINT8                           ucRlcSizeLevelCnt;        /*��Ч�ĵ�λ�ȼ�*/
    VOS_UINT8                           aucReserve1[1];
    WTTF_MNTN_RLC_PDU_SIZE_INFO_STRU    astMntnRlcPduSizeInfo[WTTF_MNTN_MAX_FLX_RLC_SIZE_LEVEL_CNT];/*��Ч��RLC SIZE,�±��ӦucPduSizeIdx*/
} TTF_OM_WCDMA_RLC_PDU_SIZE_TRANS_INFO_STRU;


/*****************************************************************************
 �ṹ��    :WTTF_MNTN_RLC_PDU_SIZE_TRANS_INFO_OBJ_STRU
 Э����  :��ά�ɲ�ʵ������RLC PDU Sizeѡ��ͳ��
 ASN.1���� :
 �ṹ˵��  : WTTF MNTN RLC Data Trans Info ����
*****************************************************************************/
typedef struct{
    VOS_UINT32                                          ulSimuClock;
    OM_TTF_WCDMA_RLC_PDU_SIZE_TRANS_INFO_REQ_STRU       stOmRlcPduSizeReq;
    TTF_OM_WCDMA_RLC_PDU_SIZE_TRANS_INFO_STRU           astMntnRlCPduSizeTransInfo[WTTF_MNTN_MAX_RB_ID + 1];
} WTTF_MNTN_RLC_PDU_SIZE_TRANS_INFO_OBJ_STRU;

/*****************************************************************************
 �ṹ��     : TTF_OM_WCDMA_RLC_PDU_SIZE_TRANS_INFO_CNF_STRU
 ��Ӧ��Ϣ: ID_WTTF_OM_RLC_PDU_SIZE_TRANS_INFO_CNF
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    PS_RSLT_CODE_ENUM_UINT32          enRslt;         /* ���ز�ѯ�ṹ�ɹ���ʧ�� */
} TTF_OM_WCDMA_RLC_PDU_SIZE_TRANS_INFO_CNF_STRU;


/*****************************************************************************
 �ṹ��     :  OM_TTF_WCDMA_UPA_DATA_STATUS_G_INFO_REQ_STRU
 ��Ӧ��Ϣ:  ID_OM_WTTF_UPA_DATA_STATUS_G_INFO_REQ
*****************************************************************************/
typedef OM_TTF_WCDMA_RLC_PDU_SIZE_TRANS_INFO_REQ_STRU OM_TTF_WCDMA_UPA_DATA_STATUS_G_INFO_REQ_STRU;


/*****************************************************************************
 �ṹ��     :  TTF_OM_WCDMA_UPA_DATA_STATUS_G_INFO_CNF_STRU
 ��Ӧ��Ϣ:  ID_WTTF_OM_UPA_DATA_STATUS_G_INFO_CNF
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    PS_RSLT_CODE_ENUM_UINT32          enRslt;         /* ���ز�ѯ�ṹ�ɹ���ʧ�� */

} TTF_OM_WCDMA_UPA_DATA_STATUS_G_INFO_CNF_STRU;

/*****************************************************************************
 �ṹ��     :  WTTF_MNTN_RLC_AM_UL_DATA_TRANS_INFO_STRU
 ��Ӧ��Ϣ:  WTTF_MNTN_RLC_AM_UL_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRlcResetNum;          /* ����Reset���� */
                                                                /* ��������������ͷ��ᷢ��Reset
                                                                1)"No_Discard after MaxDAT number of transmissions" is configured and VT(DAT) equals the value MaxDAT (see subclause 9.7.3.4);
                                                                2)VT(MRW) equals the value MaxMRW;
                                                                3)A STATUS PDU or a piggybacked STATUS PDU including "erroneous Sequence Number" is received (see clause 10);
                                                                */

    VOS_UINT32                          ulLowRlcPduTxBytes;     /*��λ:���͵�RLC PDU�ֽ�����ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ����͵�MAC���RLC PDUs���ֽ��������а����²��ɵ����ݺͿ���PDU���ش���PDU��Reset PDU��*/
    VOS_UINT32                          ulHighRlcPduTxBytes;    /*��λ:���͵�RLC PDU�ֽ�����ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ����͵�MAC���RLC PDUs���ֽ��������а����²��ɵ����ݺͿ���PDU���ش���PDU��Reset PDU��*/

    VOS_UINT32                          ulLowRlcSduTxBytes;        /*��λ:���͵�RLC SDU�ֽ�����ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ����ֶγ�PDU��SDUs���ֽ���*/
    VOS_UINT32                          ulHighRlcSduTxBytes;    /*��λ:���͵�RLC SDU�ֽ�����ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ����ֶγ�PDU��SDUs���ֽ���*/

    VOS_UINT32                          ulCurPrdRlcSduTxBytes;  /* ��ǰ�ϱ������ڷ���RLC SDU�ֽ��� */
    VOS_UINT32                          ulRlcDataPduTxNum;        /* ���͵�����PDU������ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ����͵ĵ�MAC����²���������PDUs���������в������ش�������PDU��*/
    VOS_UINT32                          ulRlcDataPduRetxNum;    /* �����ش�������PDU������ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ������ش���PDU������ͬһ��PDU�ش���Σ��򵱶���ۼӣ�,�²���������PDU���������͵�����PDU���� �� �����ش�������PDU����*/
    VOS_UINT32                          ulRlcNackedPduNum;      /* ��ȷ�ϵ�PDU����:ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ,�ܹ��ӶԶ��յ���ȷ�ϵ�PDU����*/
    VOS_UINT32                          ulRlcCtrlPduTxNum;        /* ���͵Ŀ���PDU����:ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ,�ܹ����͵�MAC��Ŀ���PDU����(���а���״̬PDU��Reset��Reset Ack PDU)*/
    VOS_UINT16                          usRlcLastTxPduSn;       /* [0..4095]���һ�η��͵�SNֵ:VtS-1 */
    VOS_UINT16                          usRlcLastAckInseqPduSn; /* [0..4095]���һ������ȷ�ϵ�SN:VtA */
    VOS_UINT16                          usRlcVacantTxWinSize;   /* [1..4095]ָVtMs-VtS */
    VOS_UINT8                           aucReserve2[2];
    VOS_UINT32                          ulRlcBo;                /* ʵ��BO */
    VOS_UINT32                          ulRlcDataPdu3ReTxNum;   /* �ش������ﵽ���ε�����PDU����*/
    VOS_UINT32                          ulRlcDataPdu4ReTxNum;   /* �ش������ﵽ�Ĵε�����PDU����*/
    VOS_UINT32                          ulRlcDataPdu5ReTxNum;   /* �ش������ﵽ��ε�����PDU����*/
    VOS_UINT32                          ulRlcDataPdu6ReTxNum;   /* �ش������ﵽ���ε�����PDU����*/
    VOS_UINT32                          ulRlcDataPduMore7ReTxNum;/* �ش������ﵽ�ߴ����ϣ������ߴΣ�������PDU����*/
} WTTF_MNTN_RLC_AM_UL_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 �ṹ��     :  WTTF_MNTN_RLC_AM_DL_DATA_TRANS_INFO_STRU
 ��Ӧ��Ϣ:  WTTF_MNTN_RLC_AM_DL_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRlcResetNum;          /* ����Reset���� */
    VOS_UINT32                          ulLowRlcPduRxBytes;        /* ��λ:���յ���RLC PDU �ֽ���: ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ���MAC����յ���RLC PDUs���ֽ��������а�������ȷ����������PDU�Ϳ���PDU���Լ��ظ����ջ��ڽ��մ��ڵ�����PDU��������CRC���󣩣���ָ����MAC���յ�������*/
    VOS_UINT32                          ulHighRlcPduRxBytes;    /* ��λ:���յ���RLC PDU �ֽ���: ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ���MAC����յ���RLC PDUs���ֽ��������а�������ȷ����������PDU�Ϳ���PDU���Լ��ظ����ջ��ڽ��մ��ڵ�����PDU��������CRC���󣩣���ָ����MAC���յ�������*/

    VOS_UINT32                          ulLowRlcSduRxBytes;     /* ��λ:���յ���SDU�ֽ���: ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ�������ɵ�SDU�ֽ��� */
    VOS_UINT32                          ulHighRlcSduRxBytes;    /* ��λ:���յ���SDU�ֽ���: ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ�������ɵ�SDU�ֽ��� */
    VOS_UINT32                          ulCurPrdRlcSduRxBytes;    /* ��ǰ�ϱ������ڽ���RLC SDU�ֽ��� */
    VOS_UINT32                          ulRlcCrcErrPduRxNum;    /* Crc Error PDU������ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ���MAC����������CRC�����PDU����*/
    VOS_UINT32                          ulRlcInvalidDataPduRxNum;    /* ��Ч����PDU����: ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ���MAC������������Ч����PDU���������а����������������PDU���ظ����ջ��ڽ��մ��ڵ�����PDU��*/
    VOS_UINT32                          ulRlcDataPduRxNum;      /* ���յ�������PDU������ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ,�ܹ���MAC������������Ч����PDU���������в������ظ����ջ��������PDU��*/
    VOS_UINT32                          ulRlcCtrlPduRxNum;      /* ���յ��Ŀ���PDU������ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ���MAC���������Ŀ���PDU���������а����˽�������Ŀ���PDU��*/
    VOS_UINT32                          ulRlcNackedPduNum;      /* ��ȷ�ϵ�PDU����:ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ,�ܹ����͵��Զ˸�ȷ�ϵ�PDU����*/
    VOS_UINT16                          usRlcLastRxInseqPduSn;  /*[0..4095]����һ��Ҫ���յ�SNֵ  */
    VOS_UINT16                          usRlcHighestPduSn;      /*[0..4095]����߽��յ�PDU���*/
} WTTF_MNTN_RLC_AM_DL_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 �ṹ��     :  WTTF_MNTN_RLC_AM_DATA_TRANS_INFO_STRU
 ��Ӧ��Ϣ:  WTTF_MNTN_RLC_AM_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                          enExist;                /* ��ʾ��ʵ���Ƿ���ڣ�0��ʾ�����ڣ�1��ʾ���� */
    VOS_UINT8                                   ucRbId;
    VOS_UINT8                                   aucReserve2[2];
    WTTF_MNTN_RLC_AM_UL_DATA_TRANS_INFO_STRU    stRlcMntnAmUlDataTransInfo;
    WTTF_MNTN_RLC_AM_DL_DATA_TRANS_INFO_STRU    stRlcMntnAmDlDataTransInfo;
} WTTF_MNTN_RLC_AM_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 �ṹ��     :  WTTF_MNTN_RLC_UM_UL_DATA_TRANS_INFO_STRU
 ��Ӧ��Ϣ:  WTTF_MNTN_RLC_UM_UL_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLowRlcPduTxBytes;     /*��λ: ���͵�RLC PDU�ֽ�����ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ����͵�MAC���RLC PDUs���ֽ���*/
    VOS_UINT32                          ulHighRlcPduTxBytes;    /*��λ: ���͵�RLC PDU�ֽ�����ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ����͵�MAC���RLC PDUs���ֽ���*/
    VOS_UINT32                          ulLowRlcSduTxBytes;        /*��λ: ���͵�RLC SDU�ֽ�����ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ����ֶγ�PDU��SDUs���ֽ���*/
    VOS_UINT32                          ulHighRlcSduTxBytes;    /*��λ: ���͵�RLC SDU�ֽ�����ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ����ֶγ�PDU��SDUs���ֽ���*/
    VOS_UINT32                          ulRlcPduTxNum;            /*���͵�RLC PDU ������ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ����͵�MAC���RLC PDUs����*/
    VOS_UINT16                          usRlcLastTxPduSn;       /*[0..4095]�����һ�η��͵�SNֵ:VtUs-1*/
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulRlcBo;                /* ʵ��BO */
} WTTF_MNTN_RLC_UM_UL_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 �ṹ��     :  WTTF_MNTN_RLC_UM_DL_DATA_TRANS_INFO_STRU
 ��Ӧ��Ϣ:  WTTF_MNTN_RLC_UM_DL_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLowRlcPduRxBytes;        /*��λ: ���յ�RLC PDU�ֽ�����ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ���MAC����յ���RLC PDUs���ֽ������������������PDU*/
    VOS_UINT32                          ulHighRlcPduRxBytes;    /*��λ: ���յ�RLC PDU�ֽ�����ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ���MAC����յ���RLC PDUs���ֽ������������������PDU*/
    VOS_UINT32                          ulLowRlcSduRxBytes;     /*��λ: ���յ���SDU�ֽ���:ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ�������ɵ�SDU�ֽ��� */
    VOS_UINT32                          ulHighRlcSduRxBytes;    /*��λ: ���յ���SDU�ֽ���:ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ�������ɵ�SDU�ֽ��� */
    VOS_UINT32                          ulRlcCrcErrPduRxNum;    /* Crc Error PDU������ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ���MAC����������CRC�����PDU����*/
    VOS_UINT32                          ulRlcInvalidPduRxNum;   /* ��ЧPDU����: ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ���MAC������������ЧPDU���������а�����Ų�������Li����ָʾǰһ��PDU�����PDU��*/
    VOS_UINT32                          ulRlcValidPduRxNum;     /* ��ЧPDU����: ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ���MAC������������ЧPDU����(��CrcError,��invalid PDU���PDU) */
    VOS_UINT16                          usRlcLastRxInseqPduSn;  /*[0..4095]�����һ�ν��յ���SNֵ:VrUs - 1 */
    VOS_UINT8                           aucReserve1[2];
} WTTF_MNTN_RLC_UM_DL_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 �ṹ��     :  WTTF_MNTN_RLC_UM_DATA_TRANS_INFO_STRU
 ��Ӧ��Ϣ:  WTTF_MNTN_RLC_UM_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                          enExist;                /* ��ʾ��ʵ���Ƿ���ڣ�0��ʾ�����ڣ�1��ʾ���� */
    VOS_UINT8                                   ucRbId;
    VOS_UINT8                                   aucReserve2[2];
    WTTF_MNTN_RLC_UM_UL_DATA_TRANS_INFO_STRU    stRlcMntnUmUlDataTransInfo;
    WTTF_MNTN_RLC_UM_DL_DATA_TRANS_INFO_STRU    stRlcMntnUmDlDataTransInfo;
} WTTF_MNTN_RLC_UM_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 �ṹ��     :  WTTF_MNTN_RLC_TM_UL_DATA_TRANS_INFO_STRU
 ��Ӧ��Ϣ:  WTTF_MNTN_RLC_TM_UL_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLowRlcSduTxBytes;     /*��λ: ���͵�RLC PDU�ֽ�����ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ����͵�MAC���RLC SDUs���ֽ���������8bit�İ�8����������ȡ��*/
    VOS_UINT32                          ulHighRlcSduTxBytes;    /*��λ: ���͵�RLC PDU�ֽ�����ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ����͵�MAC���RLC SDUs���ֽ���������8bit�İ�8����������ȡ��*/
    VOS_UINT32                          ulLowRlcDiscardSduTxBytes;  /*��λ: Discard RLC SDU�ֽ�����ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ�������RLC SDUs���ֽ���������8bit�İ�8����������ȡ��*/
    VOS_UINT32                          ulHightRlcDiscardSduTxBytes;  /*��λ: Discard RLC SDU�ֽ�����ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ�������RLC SDUs���ֽ���������8bit�İ�8����������ȡ��*/
    VOS_UINT32                          ulRlcPduTxNum;            /* ���͵�RLC PDU������ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ����͵�MAC���RLC PDUs�ĸ���*/
} WTTF_MNTN_RLC_TM_UL_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 �ṹ��     :  WTTF_MNTN_RLC_TM_DL_DATA_TRANS_INFO_STRU
 ��Ӧ��Ϣ:  WTTF_MNTN_RLC_TM_DL_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLowRlcSduRxBytes;     /*��λ: ���յ���SDU�ֽ���:ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ����յ���SDU�ֽ���������8bit�İ�8����������ȡ�� */
    VOS_UINT32                          ulHighRlcSduRxBytes;    /*��λ: ���յ���SDU�ֽ���:ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ����յ���SDU�ֽ���������8bit�İ�8����������ȡ�� */
    VOS_UINT32                          ulLowRlcPduRxBytes;        /* ��λ:���յ���RLC PDU �ֽ���: ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ���MAC����յ���RLC PDUs���ֽ��������а�����CrcError��PDU������ָ����MAC���յ�������������8bit�İ�8����������ȡ��*/
    VOS_UINT32                          ulHighRlcPduRxBytes;    /* ��λ:���յ���RLC PDU �ֽ���: ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ���MAC����յ���RLC PDUs���ֽ��������а�����CrcError��PDU������ָ����MAC���յ�������������8bit�İ�8����������ȡ��*/
    VOS_UINT32                          ulRlcCrcErrPduRxNum;    /* Crc Error PDU������ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ���MAC����������CRC�����PDU����*/
    VOS_UINT32                          ulRlcValidPduRxNum;     /* ��ЧPDU����: ͳ�Ƶ��ǴӲ�ѯʱ�̿�ʼ��ʱ���ܹ���MAC������������ЧPDU����(��CrcError���PDU) */
} WTTF_MNTN_RLC_TM_DL_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 �ṹ��     :  WTTF_MNTN_RLC_TM_DATA_TRANS_INFO_STRU
 ��Ӧ��Ϣ:  WTTF_MNTN_RLC_TM_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                          enExist;                /* ��ʾ��ʵ���Ƿ���ڣ�0��ʾ�����ڣ�1��ʾ���� */
    VOS_UINT8                                   ucRbId;
    VOS_UINT8                                   aucReserve2[2];
    WTTF_MNTN_RLC_TM_UL_DATA_TRANS_INFO_STRU    stRlcMntnTmUlDataTransInfo;
    WTTF_MNTN_RLC_TM_DL_DATA_TRANS_INFO_STRU    stRlcMntnTmDlDataTransInfo;
} WTTF_MNTN_RLC_TM_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 �ṹ��    :TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ID_WTTF_OM_RLC_DATA_TRANS_INFO_IND�ϱ���ѯ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulCurPrdRlcSduTxRate;  /* ��ǰ�ϱ������ڷ���RLC SDU�ֽ��� */
    VOS_UINT32                              ulCurPrdRlcSduRxRate;  /* ��ǰ�ϱ������ڷ���RLC SDU�ֽ��� */
    WTTF_MNTN_RLC_AM_DATA_TRANS_INFO_STRU   astMntnRlcAmDataTransInfo[WTTF_MNTN_MAX_AM_RB_NUM];
    WTTF_MNTN_RLC_UM_DATA_TRANS_INFO_STRU   astMntnRlcUmDataTransInfo[WTTF_MNTN_MAX_UM_RB_NUM];
    WTTF_MNTN_RLC_TM_DATA_TRANS_INFO_STRU   astMntnRlcTmDataTransInfo[WTTF_MNTN_MAX_TM_RB_NUM];
} TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    :WTTF_MNTN_RLC_DATA_TRANS_INFO_OBJ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WTTF MNTN RLC Data Trans Info ����
*****************************************************************************/
typedef struct{
    VOS_UINT32                                     ulSimuClock;
    OM_TTF_WCDMA_RLC_DATA_TRANS_INFO_REQ_STRU      stOmRlcReq;
    TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_IND_STRU      stRlcOmInd;
    VOS_UINT8                                      aucAmReTxNumPerDataPdu[WTTF_MNTN_MAX_AM_RB_NUM][WTTF_MNTN_RLC_AM_MAX_SN_NUM];
} WTTF_MNTN_RLC_DATA_TRANS_INFO_OBJ_STRU;

/*****************************************************************************
 �ṹ��     :  OM_IPS_ADVANCED_TRACE_CONFIG_REQ_STRU
 ��Ӧ��Ϣ:  ID_OM_IPS_ADVANCED_TRACE_CONFIG_REQ
*****************************************************************************/
typedef struct
{
    IPS_MNTN_BRIDGE_TRACE_CFG_STRU              stBridgeArpTraceCfg;        /*���ò���������Ϣ*/
    IPS_MNTN_INPUT_TRACE_CFG_STRU               stPreRoutingTraceCfg;       /*���ò���TCP/IPЭ��ջ������Ϣ*/
    IPS_MNTN_OUTPUT_TRACE_CFG_STRU              stPostRoutingTraceCfg;      /*���ò���TCP/IPЭ��ջ������Ϣ*/
    IPS_MNTN_LOCAL_TRACE_CFG_STRU               stLocalTraceCfg;            /*���ò���TCP/IPЭ��ջ������Ϣ*/
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8     enAdsIPConfig;
    VOS_UINT8                                   aucRsv[3];                  /* ����λ */
}IPS_MNTN_TRACE_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��     :  OM_IPS_ADVANCED_TRACE_CONFIG_REQ_STRU
 ��Ӧ��Ϣ:  OM_IPS_ADVANCED_TRACE_CONFIG_REQ_STRU
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU            stDiagHdr;
    IPS_MNTN_TRACE_CONFIG_REQ_STRU     stIpsAdvanceCfgReq;
}OM_IPS_ADVANCED_TRACE_CONFIG_REQ_STRU;


/*****************************************************************************
 �ṹ��     :  IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU
 ��Ӧ��Ϣ:  ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF
*****************************************************************************/
typedef struct
{
    PS_RSLT_CODE_ENUM_UINT32           enRslt;                 /* ���ز�ѯ�ṹ�ɹ���ʧ�ܣ�PS_SUCC��ʾ�ɹ���PS_FAIL��ʾʧ�� */
}IPS_MNTN_TRACE_CONFIG_CNF_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU         stDiagHdr;
    IPS_MNTN_TRACE_CONFIG_CNF_STRU  stIpsAdvanceCfgCnf;
}IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU;


/*****************************************************************************
 �ṹ��     :  OM_IPS_MNTN_INFO_CONFIG_REQ_STRU
 ��Ӧ��Ϣ:  ID_OM_IPS_MNTN_INFO_CONFIG_REQ
*****************************************************************************/
typedef struct
{
    IPS_MNTN_INFO_ACTION_ENUM_UINT16    enCommand;
    VOS_UINT16                          usTimeLen;              /*��λ���� */
}IPS_MNTN_INFO_CFG_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU             stDiagHdr;
    IPS_MNTN_INFO_CFG_REQ_STRU          stIpsMntnCfgReq;
}OM_IPS_MNTN_INFO_CONFIG_REQ_STRU;


/*****************************************************************************
 �ṹ��     :  IPS_OM_MNTN_INFO_CONFIG_CNF_STRU
 ��Ӧ��Ϣ:  ID_IPS_OM_MNTN_INFO_CONFIG_CNF
*****************************************************************************/
typedef struct
{
    IPS_MNTN_RESULT_TYPE_ENUM_UINT32    enRslt;
    IPS_MNTN_INFO_ACTION_ENUM_UINT16    enCommand;
    VOS_UINT8                           aucRsv[2];
}IPS_MNTN_INFO_CFG_CNF_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU    stDiagHdr;
    IPS_MNTN_INFO_CFG_CNF_STRU stIpsMntnCfgCnf;
}IPS_OM_MNTN_INFO_CONFIG_CNF_STRU;


/*****************************************************************************
   Gģ��ά�ɲ���Ϣ
*****************************************************************************/
/*****************************************************************************
 �ṹ��     :  GRM_MNTN_COM_INFO_STRU
 ��Ӧ��Ϣ:  GRM_MNTN_GRM_OM_INFO
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulTlli;                 /* 0xffffffff:��Чֵ */
    GRM_TBF_INFO_TEST_MODE_ENUM_UINT8    ucTestMode;             /* GPRS����ʱ��ʵ�ʹ���ģʽ, 0xff:��Чֵ */
    VOS_UINT8                            aucRsv[1];
    VOS_UINT16                           usLlcPduNum;            /* aģʽ�´����ص�LLC PDU��Ŀ, 0xffff:��Чֵ */
}GRM_MNTN_COM_INFO_STRU;

/*****************************************************************************
 �ṹ��     :  GRM_MNTN_UL_TBF_STRU
 ��Ӧ��Ϣ:  GRM_MNTN_GRM_OM_INFO
*****************************************************************************/
typedef struct
{
    GRM_TBF_INFO_RLC_MODE_ENUM_UINT8              ucUlRlcMode;        /* 0:GRLC_MODE_AM, 1:GRLC_MODE_UM, 0xff:��Чֵ */
    GRM_TBF_INFO_COUNTDOWN_FLAG_ENUM_UINT8        ucCountdownFlag;    /* �˱�־ֻ�ڷ���չ����TBF��ʹ�ã���ʾ:�Ƿ���뵹��������.
                                                                         VOS_YES:�����˵�����, VOS_NO:û�н���, 0xff:��Чֵ */
    GRM_TBF_INFO_EDGE_CODE_SCHEME_ENUM_UINT16     usUlCodeType;       /* EDGE_CODE_SCHEME_BUTT: 0xffff ��Чֵ */
    VOS_UINT8                                     ucUlTfi;            /* 0xff: ��Чֵ */
    GRM_TBF_INFO_TI_ENUM_UINT8                    ucTi;               /* 1: ��ͻ���δ���, 0: ��ͻ������, 0xff: ��Чֵ */
    VOS_UINT8                                     aucRsv[2];
}GRM_MNTN_UL_TBF_STRU;

/*****************************************************************************
 �ṹ��     :  GRM_MNTN_UL_ENTITY_INFO_STRU ������Ϣ
 ��Ӧ��Ϣ:  GRM_MNTN_GRM_OM_INFO
*****************************************************************************/
typedef struct
{
    /*====================*/ /* ״̬��Ϣ */
    GRM_TBF_INFO_TBF_MODE_ENUM_UINT8         ucUlTbfMode;                    /* 1:Extend ��չTBF, 0: no-extend ����չ, 0xff:��Чֵ*/
    VOS_UINT8                                ucBsCvMax;                      /* Range: 0 to 15. 0xff:��Чֵ */
    GRM_TBF_INFO_TIMESLOT_FLAG_ENUM_UINT8    aucUlTsFlag[GRM_MNTN_TS_TOTAL]; /* 0xff: ��Чֵ */
    VOS_UINT8                                aucRsv[2];
    GRM_MNTN_UL_TBF_STRU                     astTbf[GRLC_MNTN_MAX_TBF_NUM];  /* Tbf��Ϣ */
}GRM_MNTN_UL_ENTITY_INFO_STRU;

/*================*/  /*������Ϣ*/
/*****************************************************************************
 �ṹ��     :  GRM_MNTN_DL_TBF_STRU
 ��Ӧ��Ϣ:  GRM_MNTN_GRM_OM_INFO
*****************************************************************************/
typedef struct
{
    /*AM:���ڿ�ά�ɲ�
    UMģʽ:�����յĿ�ı��뷽ʽ���ṩ��UMģʽ�����ʹ�ã�
    ��ʼֵΪEDGE_CODE_SCHEME_BUTT��������δ�յ���ȷ�����п� */
    GRM_TBF_INFO_EDGE_CODE_SCHEME_ENUM_UINT16     usDlCodeType;       /* EDGE_CODE_SCHEME_BUTT: 0xffff ��Чֵ */
    GRM_TBF_INFO_FINALBLKRXED_ENUM_UINT8          ucFinalBlkRxed;     /* FBI=1�Ŀ��Ƿ��Ѿ����յ�, 0xff: ��Чֵ */
    GRM_TBF_INFO_RLC_MODE_ENUM_UINT8              ucDlRlcMode;        /* 0:AM, 1:UM, 0xff: ��Чֵ */
    VOS_UINT8                                     ucDlTfi;            /* TFI value 0xff: ��Чֵ */
    VOS_UINT8                                     aucRsv[3];
}GRM_MNTN_DL_TBF_STRU;

/*****************************************************************************
 �ṹ��     :  GRM_MNTN_DL_ENTITY_INFO_STRU
 ��Ӧ��Ϣ:  GRM_MNTN_GRM_OM_INFO
*****************************************************************************/
typedef struct
{
	GRM_TBF_INFO_TIMESLOT_FLAG_ENUM_UINT8    aucDlTsFlag[GRM_MNTN_TS_TOTAL];                 /* ����ʱ϶���� 0xff: ��Чֵ*/
    GRM_MNTN_DL_TBF_STRU                     astTbf[GRLC_MNTN_MAX_TBF_NUM];   /* ��ǰֻ֧�ֵ�TBF */
}GRM_MNTN_DL_ENTITY_INFO_STRU;

/*================*/  /*�ϱ�OM������ṹ��Ϣ*/
/*****************************************************************************
 �ṹ��     :  GRM_MNTN_GRM_OM_INFO_STRU
 ��Ӧ��Ϣ:  GRM_MNTN_GRM_OM_INFO
*****************************************************************************/
typedef struct
{
    GRM_MNTN_COM_INFO_STRU          stGrmMntnComInfo;   /*������Ϣ*/
    GRM_MNTN_UL_ENTITY_INFO_STRU    stGrmMntnUlInfo;    /*������Ϣ*/
    GRM_MNTN_DL_ENTITY_INFO_STRU    stGrmMntnDlInfo;    /*������Ϣ*/
}GRM_MNTN_GRM_OM_INFO_STRU;

/*****************************************************************************
 �ṹ��     :  GRM_MNTN_OM_GRM_INFO_CFG_REQ_STRU
 ��Ӧ��Ϣ:  ID_GRM_MNTN_OM_GRM_INFO_CFG_REQ
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;      /* ͸����Ϣͷ*/

    GRM_MNTN_OM_REPORT_ACTION_ENUM_UINT16   enStartOrStop;
    VOS_UINT16                              usRptPeriod;    /* ��λ: s */
}GRM_MNTN_OM_GRM_INFO_CFG_REQ_STRU;


/*****************************************************************************
 �ṹ��     :  GRM_MNTN_GRM_OM_INFO_CFG_CNF_STRU
 ��Ӧ��Ϣ:  ID_GRM_MNTN_GRM_OM_INFO_CFG_CNF
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;     /* ͸����Ϣͷ*/

    GRM_RESULT_TYPE_ENUM_UINT32             enRslt;
    GRM_MNTN_OM_REPORT_ACTION_ENUM_UINT16   enStartOrStop;
    VOS_UINT16                              usRptPeriod;   /* ��λ: s */
}GRM_MNTN_GRM_OM_INFO_CFG_CNF_STRU;


/*****************************************************************************
 �ṹ��     :  GRM_MNTN_OM_GRM_THROUGHPUT_CFG_REQ_STRU
 ��Ӧ��Ϣ:  ID_GRM_MNTN_OM_GRM_THROUGHPUT_CFG_REQ
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;

    GRM_MNTN_OM_REPORT_ACTION_ENUM_UINT16   enStartOrStop;
    VOS_UINT8                               aucRsv[2];
}GRM_MNTN_OM_GRM_THROUGHPUT_CFG_REQ_STRU;


/*****************************************************************************
 �ṹ��     :  GRM_MNTN_GRM_OM_THROUGHPUT_CFG_CNF_STRU
 ��Ӧ��Ϣ:  ID_GRM_MNTN_GRM_OM_THROUGHPUT_CFG_CNF
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;

    GRM_RESULT_TYPE_ENUM_UINT32             enRslt;
    GRM_MNTN_OM_REPORT_ACTION_ENUM_UINT16   enStartOrStop;
    VOS_UINT8                               aucRsv[2];
}GRM_MNTN_GRM_OM_THROUGHPUT_CFG_CNF_STRU;

typedef TTF_MNTN_TRACE_DATA_CONFIG_STRU GTTF_MNTN_LL_GRM_TRACE_CONFIG_STRU;
typedef TTF_MNTN_TRACE_DATA_CONFIG_STRU GTTF_MNTN_SN_LL_TRACE_CONFIG_STRU;
typedef TTF_MNTN_TRACE_DATA_CONFIG_STRU GTTF_MNTN_RABM_SN_TRACE_CONFIG_STRU;

/*****************************************************************************
 �ṹ��     : GTTF_TRACE_MSG_CONFIG_STRU
 ��Ӧ��Ϣ: GTTF_TRACE_MSG_CONFIG_STRU
*****************************************************************************/
typedef struct
{
    GTTF_MNTN_LL_GRM_TRACE_CONFIG_STRU          stllGrmCfg;
    GTTF_MNTN_SN_LL_TRACE_CONFIG_STRU           stSnllCfg;
    GTTF_MNTN_RABM_SN_TRACE_CONFIG_STRU         stRabmSnCfg;
}GTTF_TRACE_MSG_CONFIG_STRU;

/*****************************************************************************
 �ṹ��     :  GRM_MNTN_OM_GTTF_ADV_TRACE_SWITCH_REQ_STRU
 ��Ӧ��Ϣ:  ID_GRM_MNTN_OM_GTTF_ADV_TRACE_SWITCH_REQ
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                     stTransHdr;
    TOOL_GTTF_CFG_SWITCH_ENUM_UINT32            enL2CfgSwitch;          /* TRACE����0:�ر�1:��*/
    GTTF_TRACE_MSG_CONFIG_STRU                  stAdvancedConfig;
}GRM_MNTN_OM_GTTF_ADV_TRACE_SWITCH_REQ_STRU;

/*****************************************************************************
 �ṹ��     :  GRM_MNTN_GTTF_OM_ADV_TRACE_SWITCH_CNF_STRU
 ��Ӧ��Ϣ:  ID_GRM_MNTN_GTTF_OM_ADV_TRACE_SWITCH_CNF
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    PS_RSLT_CODE_ENUM_UINT32          enRslt;         /* ���ز�ѯ�ṹ�ɹ���ʧ�� */
}GRM_MNTN_GTTF_OM_ADV_TRACE_SWITCH_CNF_STRU;

/*****************************************************************************
   CP�Ϲ���IP���ġ�PPP֮֡���ά��
*****************************************************************************/
/*****************************************************************************
 �ṹ��     :  IPS_MNTN_CCORE_VISP_LOG_CONFIG_REQ_STRU
 ��Ӧ��Ϣ:
*****************************************************************************/
typedef struct
{
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8         enVISPLogOutConfig;             /* VISP��־�ܿ��� */
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_E_ENUM_UINT8     enVISPRunLogLevelConfig;        /* VISP RUN��־�������� */
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8         enVISPUnEncryptPktCapConfig;    /* VISP�Ǽ��ܱ���ץ������ */
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8         enVISPEncryptPktCapConfig;      /* VISP���ܱ���ץ������ */
}IPS_MNTN_CCORE_VISP_LOG_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��     :  OM_IPS_CCORE_ADVANCED_TRACE_CONFIG_REQ_STRU
 ��Ӧ��Ϣ:  ID_OM_IPS_CCORE_ADVANCED_TRACE_CONFIG_REQ
*****************************************************************************/
typedef struct
{
    IPS_MNTN_CCORE_BRIDGE_TRACE_CFG_STRU        stBridgeTraceCfg;       /*���ò���������Ϣ*/
    IPS_MNTN_CCORE_INPUT_TRACE_CFG_STRU         stInputTraceCfg;        /*���ò���TCP/IPЭ��ջ������Ϣ*/
    IPS_MNTN_CCORE_OUTPUT_TRACE_CFG_STRU        stOutputTraceCfg;       /*���ò���TCP/IPЭ��ջ������Ϣ*/
    IPS_MNTN_CCORE_VISP_LOG_CONFIG_REQ_STRU     stVispLogConfig;
}IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU               stDiagHdr;
    IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU  stIpsCcoreCfgReq;
}OM_IPS_CCORE_ADVANCED_TRACE_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��     :  IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF_STRU
 ��Ӧ��Ϣ:  ID_IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF
*****************************************************************************/
typedef struct
{
    PS_RSLT_CODE_ENUM_UINT32            enRslt;                 /* ���ز�ѯ�ṹ�ɹ���ʧ�ܣ�PS_SUCC��ʾ�ɹ���PS_FAIL��ʾʧ�� */
}IPS_MNTN_CCORE_TRACE_CONFIG_CNF_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU              stDiagHdr;
    IPS_MNTN_CCORE_TRACE_CONFIG_CNF_STRU stIpsCcoreCfgCnf;
}IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��     :  OM_IPS_CCORE_MNTN_INFO_CONFIG_REQ_STRU
 ��Ӧ��Ϣ:  ID_OM_IPS_CCORE_MNTN_INFO_CONFIG_REQ
*****************************************************************************/
typedef struct
{
    IPS_MNTN_CCORE_INFO_ACTION_ENUM_UINT16    enCommand;
    VOS_UINT16                                usTimeLen;              /*��λ���� */
}IPS_MNTN_CCORE_INFO_CFG_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stDiagHdr;
    IPS_MNTN_CCORE_INFO_CFG_REQ_STRU  stIpsCcoreMntnCfgReq;
}OM_IPS_CCORE_MNTN_INFO_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��     :  IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF_STRU
 ��Ӧ��Ϣ:  ID_IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF
*****************************************************************************/
typedef struct
{
    IPS_MNTN_CCORE_RESULT_TYPE_ENUM_UINT32    enRslt;
    IPS_MNTN_CCORE_INFO_ACTION_ENUM_UINT16    enCommand;
    VOS_UINT8                                 aucRsv[2];
}IPS_MNTN_CCORE_INFO_CFG_CNF_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU             stDiagHdr;
    IPS_MNTN_CCORE_INFO_CFG_CNF_STRU    stIpsCcoreMntnCfgCnf;
}IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF_STRU;

/*****************************************************************************
   1X�Ŀ�ά�ɲ���Ϣ
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : OM_CTTF_1X_MNTN_GENERIC_CONFIG_STRU
 �ṹ˵��  : 1X��ͨ����������ṹ
*****************************************************************************/
typedef struct
{
    TTF_MNTN_RPT_CMD_ENUM_UINT8             enCommand;      /* ��ʼ��ֹͣ�ϱ� */
    VOS_UINT8                               aucReserve[3];
    CTTF_1X_MAC_MNTN_RPT_PERIOD_ENUM_UINT32 enRptPeriod;    /* �ϱ�����, ��λ: ms */
} OM_CTTF_1X_MNTN_GENERIC_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : OM_CTTF_1X_MNTN_RLP_GENERIC_CONFIG_STRU
 �ṹ˵��  : 1X��RLP��������ṹ
*****************************************************************************/
typedef struct
{
    TTF_MNTN_RLP_RPT_CMD_ENUM_UINT8         enCommand;      /* ��ʼ��ֹͣ�ϱ������ */
    VOS_UINT8                               aucReserve[3];
    CTTF_1X_MAC_MNTN_RPT_PERIOD_ENUM_UINT32 enRptPeriod;    /* �ϱ�����, ��λ: ms */
} OM_CTTF_1X_MNTN_RLP_GENERIC_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : OM_CTTF_1X_MNTN_COMM_GENERIC_CONFIG_STRU
 �ṹ˵��  : 1X��ͨ����������ṹ
*****************************************************************************/
typedef struct
{
    TTF_MNTN_COMM_RPT_CMD_ENUM_UINT8        enCommand;      /* ��ʼ��ֹͣ�ϱ������ */
    VOS_UINT8                               aucReserve[3];
    CTTF_1X_MAC_MNTN_RPT_PERIOD_ENUM_UINT32 enRptPeriod;    /* �ϱ�����, ��λ: ms */
} OM_CTTF_1X_MNTN_COMM_GENERIC_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU
 �ṹ˵��  : HRPDͨ����������ṹ
*****************************************************************************/
typedef struct
{
    TTF_MNTN_COMM_RPT_CMD_ENUM_UINT8        enCommand;      /* ��ʼ��ֹͣ�ϱ������ */
    VOS_UINT8                               aucReserve[3];
    CTTF_HRPD_MNTN_RPT_PERIOD_ENUM_UINT32   enRptPeriod;    /* �ϱ�����, ��λ: ms */
} OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : OM_CTTF_HRPD_MNTN_COMM_CONFIG_STRU
 �ṹ˵��  : HRPDͨ����������ṹ
*****************************************************************************/
typedef struct
{
    TTF_MNTN_RPT_CMD_ENUM_UINT8                 enCommand;      /* ��ʼ��ֹͣ�ϱ� */
    VOS_UINT8                                   aucReserve[3];
    CTTF_HRPD_MNTN_RTC_RPT_PERIOD_ENUM_UINT32   enRptPeriod; /* �ϱ�����, ��λ: ms */
} OM_CTTF_HRPD_MNTN_COMM_CONFIG_STRU;

/*****************************************************************************
 �ṹ��     :  OM_CTTF_1X_MNTN_CONFIG_REQ_STRU
 ��Ӧ��Ϣ:  ID_OM_CTTF_1X_MNTN_CONFIG_REQ
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                     stTransHdr;

    /* ����CDMA 5.12s����, �ο�QXDM, ����ÿ1.28s�ϱ�һ�� */
    OM_CTTF_1X_MNTN_GENERIC_CONFIG_STRU         stFwdLinkInfo;    /* 1X Forward Link Info, �ϱ�����: 1280ms */
    OM_CTTF_1X_MNTN_GENERIC_CONFIG_STRU         stRevLinkInfo;    /* 1X Reverse Link Info, �ϱ�����: 1280ms */
    OM_CTTF_1X_MNTN_RLP_GENERIC_CONFIG_STRU     stRlpStatistics;  /* 1X RLP statistics, �ϱ�����: 1280ms */
    OM_CTTF_1X_MNTN_COMM_GENERIC_CONFIG_STRU    stCommonStatistics;    /* Common Channel statistics, �ϱ�����: 1280ms */
} OM_CTTF_1X_MNTN_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��     :  OM_CTTF_HRPD_MNTN_CONFIG_REQ_STRU
 ��Ӧ��Ϣ:  ID_OM_CTTF_HRPD_MNTN_CONFIG_REQ
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                     stTransHdr;

    /* ����CDMA 5.12s����, ����ÿ1.28s�ϱ�һ�� */
    OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU       stMacStatistics;    /* HRPD MAC Statistics, �ϱ�����: 1280ms */
    OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU       stRlpStatistics;    /* HRPD RLP Statistics, �ϱ�����: 1280ms */
    OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU       stMfpaStatistics;   /* MFPA RLP Statistics, �ϱ�����: 1280ms */
    OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU       stEmpaStatistics;   /* EMPA RLP Statistics, �ϱ�����: 1280ms */
    OM_CTTF_HRPD_MNTN_COMM_CONFIG_STRU          stRtc3PktInfo;      /* RTC3 Packet Info, �ϱ�����: 640ms */
    OM_CTTF_HRPD_MNTN_COMM_CONFIG_STRU          stT2pStatistics;    /* T2P Statistics, �ϱ�����: 640ms */
    OM_CTTF_HRPD_MNTN_COMM_CONFIG_STRU          stRtc3HarqInfo;     /* RTC3 Harq Info, �ϱ�����: 640ms */
    OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU       stRtc3AckInfo;      /* RTC3 ACK Info, �ϱ�����: 1280ms */
} OM_CTTF_HRPD_MNTN_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��     :  CTTF_OM_HRPD_MNTN_CONFIG_CNF_STRU
 ��Ӧ��Ϣ:  ID_CTTF_OM_HRPD_MNTN_CONFIG_CNF
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;

    PS_RSLT_CODE_ENUM_UINT32                enRslt;         /* ���óɹ���ʧ�� */
    VOS_UINT32                              ulReason;       /* ������ʧ�ܵ�ԭ�� */
} CTTF_OM_HRPD_MNTN_CONFIG_CNF_STRU;


/*****************************************************************************
 �ṹ��     :  CTTF_OM_1X_MNTN_CONFIG_CNF_STRU
 ��Ӧ��Ϣ:  ID_CTTF_OM_1X_MNTN_CONFIG_CNF
 ˵��: ע��OM�ںϺ�, HIDS��Xģ�����ÿ�����Ϣ����, ��ͬ��GUģ
       �ϱ���CNF��Ϣ
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;

    PS_RSLT_CODE_ENUM_UINT32                enRslt;         /* ���óɹ���ʧ�� */
    VOS_UINT32                              ulReason;       /* ������ʧ�ܵ�ԭ�� */
} CTTF_OM_1X_MNTN_CONFIG_CNF_STRU;


/*****************************************************************************
 �ṹ��    : CTTF_1X_MAC_MNTN_FWD_LINK_PER_INFO_STRU
 �ṹ˵��  : ĳForward�ŵ���ͳ��ֵ
*****************************************************************************/
typedef struct
{
    CTTF_1X_MAC_MNTN_RATE_ENUM_UINT8       enRate;  /* ��ЧֵΪBUTT */
    VOS_UINT8                              ucPercentage;    /* �ɹ������Ŀ�ٷֱȷ���, [0..100], ��Чֵ0xFF */
    VOS_UINT8                              aucReserved[2];  /* �����ֽ�, ������Чֵ��д, ֵΪ0 */
}CTTF_1X_MAC_MNTN_FWD_LINK_PER_INFO_STRU;

/*****************************************************************************
 �ṹ��     :  CTTF_OM_1X_MNTN_FWD_LINK_IND_STRU
 ��Ӧ��Ϣ:  ID_CTTF_OM_1X_MNTN_FWD_LINK_IND
 ˵��:  �����ϱ���Ϣ, ��API����ʱ��ָ��ָ���ϱ����ݼ���
 �ṹ˵��  : ��Forward�ŵ���ͳ��ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usPrimId;
    VOS_UINT16                                  usToolId;

    CTTF_1X_MAC_MNTN_FWD_LINK_PER_INFO_STRU     astFch[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];   /* FCHͳ��ֵ */
    CTTF_1X_MAC_MNTN_FWD_LINK_PER_INFO_STRU     astDcch[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];  /* DCCHͳ��ֵ */
    CTTF_1X_MAC_MNTN_FWD_LINK_PER_INFO_STRU     astSch0[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];  /* SCHͳ��ֵ */
} CTTF_OM_1X_MNTN_FWD_LINK_IND_STRU;
/*****************************************************************************
 �ṹ��     :  CTTF_OM_PPP_MNTN_CONFIG_REQ_STRU
 ��Ӧ��Ϣ:  ID_OM_PPP_MNTN_CONFIG_REQ
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                     stTransHdr;

    TTF_MNTN_COMM_RPT_CMD_ENUM_UINT8            enCommand;      /* ��ʼ��ֹͣ����� */
    VOS_UINT8                                   aucReserve[3];
} CTTF_OM_PPP_MNTN_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��     :  CTTF_HRPD_MNTN_PPPC_STATISTICS_REPORT_STRU
 ��Ӧ��Ϣ:  pppc�ӿ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulSuccCnt;
    VOS_UINT32                  ulFailCnt;
    VOS_UINT32                  ulNameOrPwdAuthFailCnt;
    VOS_UINT32                  ulInvalidIpAddrCnt;
    VOS_UINT32                  ulInvalidDnsAddrCnt;
    VOS_UINT32                  ulOtherFail;
}CTTF_HRPD_MNTN_PPP_STATISTICS_REPORT_STRU;

/*****************************************************************************
 �ṹ��     :  CTTF_OM_PPPC_MNTN_STATISTICS_IND_STRU
 ��Ӧ��Ϣ:  ID_PPP_OM_MNTN_STATISTIC_INFO
 ˵��:  �����ϱ���Ϣ, ��API����ʱ��ָ��ָ���ϱ����ݼ���
 �ṹ˵��  : 1X�����ŵ���ͳ��ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usPrimId;
    VOS_UINT16                                  usToolId;
    CTTF_HRPD_MNTN_PPP_STATISTICS_REPORT_STRU   stPppcStatisticInfo;
} CTTF_OM_PPPC_MNTN_STATISTICS_IND_STRU;

/*****************************************************************************
 �ṹ��     :  CTTF_OM_PPP_MNTN_CONFIG_CNF_STRU
 ��Ӧ��Ϣ:  ID_CTTF_OM_PPP_MNTN_CONFIG_CNF
 ˵��:
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;

    PS_RSLT_CODE_ENUM_UINT32                enRslt;         /* ���óɹ���ʧ�� */
    VOS_UINT32                              ulReason;       /* ������ʧ�ܵ�ԭ�� */
} CTTF_OM_PPP_MNTN_CONFIG_CNF_STRU;


/* CTTF_OM_1X_MNTN_xxx_IND_STRU�ϱ���Ϣ��ͷ�ĳ��ȣ�sizeof(usPrimId)+sizeof(usToolId) */
#define  CTTF_OM_1X_MNTN_IND_HEAD_BYTE_SIZE     (4)

/* CTTF_OM_HRPD_MNTN_xxx_IND_STRU�ϱ���Ϣ��ͷ�ĳ��ȣ�sizeof(usPrimId)+sizeof(usToolId) */
#define  CTTF_OM_HRPD_MNTN_IND_HEAD_BYTE_SIZE   (4)


/*****************************************************************************
 �ṹ��    : CTTF_1X_MAC_MNTN_REV_LINK_PER_INFO_STRU
 �ṹ˵��  : ĳReverse�ŵ���ͳ��ֵ
*****************************************************************************/
typedef struct
{
    CTTF_1X_MAC_MNTN_RATE_ENUM_UINT8       enRate;  /* ��ЧֵΪBUTT */
    VOS_UINT8                              aucReserved[3]; /* �����ֽ�, ������Чֵ��д, ֵΪ0 */
} CTTF_1X_MAC_MNTN_REV_LINK_PER_INFO_STRU;

/*****************************************************************************
 �ṹ��     :  CTTF_OM_1X_MNTN_REV_LINK_IND_STRU
 ��Ӧ��Ϣ:  ID_CTTF_OM_1X_MNTN_REV_LINK_IND
 ˵��:  �����ϱ���Ϣ, ��API����ʱ��ָ��ָ���ϱ����ݼ���
 �ṹ˵��  : ��Reverse�ŵ���ͳ��ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usPrimId;
    VOS_UINT16                                  usToolId;

    CTTF_1X_MAC_MNTN_REV_LINK_PER_INFO_STRU     astFch[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];
    CTTF_1X_MAC_MNTN_REV_LINK_PER_INFO_STRU     astDcch[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];
    CTTF_1X_MAC_MNTN_REV_LINK_PER_INFO_STRU     astSch0[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];
} CTTF_OM_1X_MNTN_REV_LINK_IND_STRU;


/*****************************************************************************
 �ṹ��    : CTTF_1X_RLP_MNTN_REV_STATISTICS_PER_ENTITY_STRU
 �ṹ˵��  : ĳRLPʵ���REV����ͳ��ֵ
*****************************************************************************/
typedef  struct
{
    VOS_UINT32    ulFrameTotalByteHigh;  /* ���͵�֡�����ֽ�������32bit��, 2015�깤�߲�֧��64bit����, �ʷֲ��ϱ�����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulFrameTotalByte;   /* ���͵�֡�����ֽ�������32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulUpperTotalByteHigh;   /* �ϲ�������͵����ֽڣ���32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulUpperTotalByte;   /* �ϲ�������͵����ֽڣ���32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTotalFrameCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulIdleFrameCnt;   /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulFchNewDataFrameCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulFchRetxFrameCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulSchNewDataFrameCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulSchRetxFrameCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNakSingle;    /* �ش�һ�κ���ճɹ��Ĵ���, ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNakDouble;   /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNakTriple;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNakAbove;    /* �ش�����3�εĴ���, ��Чֵ: 0xFFFFFFFF */
} CTTF_1X_RLP_MNTN_REV_STATISTICS_PER_ENTITY_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_1X_RLP_MNTN_FWD_STATISTICS_PER_ENTITY_STRU
 �ṹ˵��  : ĳRLPʵ���FWD����ͳ��ֵ
*****************************************************************************/
typedef  struct
{
    VOS_UINT32    ulFrameTotalByteHigh;  /* ���յ�֡�����ֽ�������32bit��, 2015�깤�߲�֧��64bit���͡���Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulFrameTotalByte;  /* ���յ�֡�����ֽ�������32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulUpperTotalByteHigh;   /* �ϲ�������յ����ֽڣ���32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulUpperTotalByte;   /* �ϲ�����ܽ��յ����ֽڣ���32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTotalFrameCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulIdleFrameCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulFillFrameCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulBlankFrameCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNullFrameCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulFchNewDataFrameCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulFchRetxFrameCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulSchNewDataFrameCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulSchRetxFrameCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNakCtrlFrameCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNakAbortTimes;   /* NAK abort����, ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulInsufficentQualityFrameCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulInvalidFcsFrameCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulInvalidTypeFieldFrameCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulInvalidCtlFieldFrameCnt;    /* ��Чֵ: 0xFFFFFFFF */
} CTTF_1X_RLP_MNTN_FWD_STATISTICS_PER_ENTITY_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_1X_RLP_MNTN_STATISTICS_PER_ENTITY_STRU
 �ṹ˵��  : ĳRLPʵ���ͳ��ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT8            ucSrId;   /* ����RLPʵ���Ψһ���, ��Чֵ: 0xFF */
    VOS_UINT8            ucMeasuredRtt;  /* ���һ�β�����RTT, ��Чֵ: 0xFF */
    VOS_UINT8            aucReserved[2];  /* �����ֽ�, ������Чֵ��д, ֵΪ0 */
    VOS_UINT16           usBSTriggeredResetTimes;  /* AT�յ�AN�ĸ�λRLP�������λRLP�Ĵ�������Чֵ: 0xFFFF */
    VOS_UINT16           usMSTriggeredResetTimes;   /* AT������λRLP�Ĵ�������Чֵ: 0xFFFF */
    VOS_UINT32           ulCurrentBo;  /* ʵʱBO, ��Чֵ: 0xFFFFFFFF */
    CTTF_1X_RLP_MNTN_REV_STATISTICS_PER_ENTITY_STRU  stRevInfo;
    CTTF_1X_RLP_MNTN_FWD_STATISTICS_PER_ENTITY_STRU  stFwdInfo;
}CTTF_1X_RLP_MNTN_STATISTICS_PER_ENTITY_STRU;

/*****************************************************************************
 �ṹ��     :  CTTF_OM_1X_MNTN_RLP_STATISTICS_IND_STRU
 ��Ӧ��Ϣ:  ID_CTTF_OM_1X_MNTN_RLP_STATISTICS_IND
 �ṹ˵��  : ��RLPʵ���ͳ��ֵ
 ˵��:  �����ϱ���Ϣ, ��API����ʱ��ָ��ָ���ϱ����ݼ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usPrimId;
    VOS_UINT16                                      usToolId;

    CTTF_1X_RLP_MNTN_STATISTICS_PER_ENTITY_STRU     astRlpEntity[CTTF_1X_RLP_MNTN_MAX_NUM];
} CTTF_OM_1X_MNTN_RLP_STATISTICS_IND_STRU;


/*****************************************************************************
 �ṹ��    : CTTF_1X_MNTN_PCH_STATISTIC_STRU
 �ṹ˵��  : PCH��ͳ��ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT32    ulTotalEncapPduFragCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ul96BitEncapPduFragCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ul192BitEncapPduFragCnt;   /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTotalEncapPduCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulInvalidCrcEncapPduCnt;   /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulChanLostCnt;   /* ��Чֵ: 0xFFFFFFFF */
} CTTF_1X_MNTN_PCH_STATISTIC_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_1X_MNTN_ACH_STATISTIC_STRU
 �ṹ˵��  : ACH��ͳ��ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT32    ulRequestTypeSduCnt;   /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulResponseTypeSduCnt;   /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulAccessProbe1Cnt;   /* ����1�γɹ��Ĵ���, ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulAccessProbe2Cnt;   /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulAccessProbe3Cnt;   /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulAccessProbe4Cnt;   /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulAccessProbe5Cnt;   /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulAccessProbeAboveCnt;    /* ����5�����ϲųɹ��Ĵ���, ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulUnsucessfulAccessAttemptCnt;   /* ����attemptʧ�ܴ���, ��Чֵ: 0xFFFFFFFF */
} CTTF_1X_MNTN_ACH_STATISTIC_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_1X_MNTN_PAGE_MSG_STATISTIC_STRU
 �ṹ˵��  : PAGE��ͳ��ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT32    ulGpmMatchedCnt;   /* ƥ���ϵ�GPM����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulSlotPageMatchedCnt;   /* Slotģʽƥ���Page����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulMismatchedPageCnt;    /* ���еĲ�ƥ���Page����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulAddrMatchedOtherMsgCnt; /* ����Page��Ϣ�⣬���еĵ�ַƥ�����Ϣ������Чֵ: 0xFFFFFFFF */
} CTTF_1X_MNTN_PAGE_MSG_STATISTIC_STRU;

/*****************************************************************************
 �ṹ��     :  CTTF_OM_1X_MNTN_COMMON_CHANNEL_STATISTICS_IND_STRU
 ��Ӧ��Ϣ:  ID_CTTF_OM_1X_MNTN_COMMON_CHANNEL_STATISTICS_IND
 ˵��:  �����ϱ���Ϣ, ��API����ʱ��ָ��ָ���ϱ����ݼ���
 �ṹ˵��  : 1X�����ŵ���ͳ��ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usToolId;

    CTTF_1X_MNTN_PCH_STATISTIC_STRU     stPch;
    CTTF_1X_MNTN_ACH_STATISTIC_STRU     stAch;
    CTTF_1X_MNTN_PAGE_MSG_STATISTIC_STRU stPage;

} CTTF_OM_1X_MNTN_COMMON_CHANNEL_STATISTICS_IND_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_PER_MAC_FLOW_STRU
 �ṹ˵��  : HRPD RTC3MAC ÿ��MAC Flow�İ�ͳ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8       ucFlowId;               /* MAC��ID����Чֵ: 0xFF */
    VOS_UINT8       aucReserved[1];         /* �����ֽ�, ������Чֵ��д, ֵΪ0xFF */
    VOS_UINT16      usActualAllocation;     /* ��λ: �ֽڣ���Чֵ: 0xFFFF */
    VOS_UINT16      usSuggestAllocation;    /* ��λ: �ֽڣ���Чֵ: 0xFFFF */
    VOS_UINT16      usRequiredQueueSize;    /* ��λ: �ֽڣ���Чֵ: 0xFFFF */
    VOS_UINT16      usQOutflow;             /* ��λ: �ֽڣ���Чֵ: 0xFFFF */
    VOS_UINT8       aucReserved1[2];        /* �����ֽ�, ������Чֵ��д, ֵΪ0xFF */
}CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_PER_MAC_FLOW_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_STRU
 �ṹ˵��  : HRPD RTC3MAC ����Ϣͳ��,PacketId����Ϊ�з����������Գ�ʼ��Ϊ-128��
             ��-128��ͼ�п���������Ȼ����0xFFFF��������(0...9),��������ϰ�ߡ�
*****************************************************************************/
typedef  struct
{
    CTTF_HRPD_MAC_TRANS_MODE_ENUM_UINT8                     enTransMode;        /* ��Чֵ: BUTT */
    CTTF_HRPD_MNTN_RTC3MAC_PAKETSIZE_INDEX_ENUM_UINT8       enPktSize;          /* ��Чֵ: BUTT */
    VOS_UINT16                                              usPaddingByteSize;  /* ��λ: �ֽڣ���Чֵ: 0xFFFF */
    VOS_INT8                                                cPacketId;          /* ��Чֵ: -128,��Чֵ0-9 */
    VOS_INT8                                                cTxT2pMax;          /* ��λ:dB,��Чֵ: -128 */
    VOS_INT8                                                cPotentialT2p;      /* ��λ:dB, ��Чֵ: -128 */
    VOS_UINT8                                               aucReserved[1];     /* �����ֽ�, ������Чֵ��д, ֵΪ0xFF */

    /* ����MAC�������� */
    CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_PER_MAC_FLOW_STRU    astMacFlow[CTTF_HRPD_RTC3MAC_MNTN_FLOW_MAX_NUM];
}CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_OM_HRPD_MNTN_RTC3MAC_LINK_PACKET_REPORT_STRU
 �ṹ˵��  : HRPD RTC3MAC ����Ϣͳ���ϱ�
 ��Ӧ��Ϣ  : ID_CTTF_OM_HRPD_MNTN_REV_LINK_PACKET_INFO_IND
 ˵��      : �����ϱ���Ϣ, ��API����ʱ��ָ��ָ���ϱ����ݼ���
*****************************************************************************/
typedef  struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usToolId;
    CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_STRU astLinkPktData[CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_PACKET_PER_FLOW];
} CTTF_OM_HRPD_MNTN_RTC3MAC_LINK_PACKET_REPORT_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_STRU
 �ṹ˵��  : HRPD RTC3MAC ÿ��MAC Flow��T2P��Ϣͳ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8       ucFlowId;       /* MAC��ID����Чֵ: 0xFF */
    VOS_INT8        cQrab;          /* -1:Ϊunloaded, 1:loaded, ��Чֵ: -128 */
    VOS_INT8        cDeltaT2p;      /* ��Чֵ: -128 */
    VOS_INT8        cBucketFactor;  /* ��Чֵ: -128 */
    VOS_INT16       sT2pInflow;     /* ��Чֵ: -32768 */
    VOS_INT16       sT2pOutflow;    /* ��Чֵ: -32768 */
    VOS_INT16       sBucketLevel;   /* ��Чֵ: -32768 */
    VOS_INT16       sBucketLevelSat;/* Saturation Bucket Level, ��Чֵ: -32768 */
} CTTF_HRPD_MNTN_RTC3MAC_LINK_T2P_PER_MAC_FLOW_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_RTC3MAC_LINK_T2P_STRU
 �ṹ˵��  : HRPD RTC3MAC T2P��Ϣͳ��
*****************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_RTC3MAC_WORK_MODE_ENUM_UINT8         enWorkMode;     /* ��Чֵ: BUTT */
    VOS_INT8                                            cQRABn;         /* -1:Ϊunloaded, 1:loaded, ��Чֵ: -128 */
    VOS_INT16                                           sFrab;          /* ��Чֵ: -32768 */

    /* ����MAC�������� */
    CTTF_HRPD_MNTN_RTC3MAC_LINK_T2P_PER_MAC_FLOW_STRU   astMacFlow[CTTF_HRPD_RTC3MAC_MNTN_FLOW_MAX_NUM];
}CTTF_HRPD_MNTN_RTC3MAC_LINK_T2P_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_OM_HRPD_MNTN_RTC3MAC_LINK_T2P_REPORT_STRU
 �ṹ˵��  : HRPD RTC3MAC T2P��Ϣͳ���ϱ�
 ��Ӧ��Ϣ  : ID_CTTF_OM_HRPD_MNTN_REV_LINK_T2P_STATISTICS_IND
 ˵��      : �����ϱ���Ϣ, ��API����ʱ��ָ��ָ���ϱ����ݼ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usToolId;
    CTTF_HRPD_MNTN_RTC3MAC_LINK_T2P_STRU    astLinkT2pData[CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_T2P_PER_FLOW];
}CTTF_OM_HRPD_MNTN_RTC3MAC_LINK_T2P_REPORT_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_RTC3MAC_HARQ_INFO_STRU
 �ṹ˵��  : HRPD RTC3MAC Harq��Ϣ��ProcessId�ȶ���Ϊ�з����������Գ�ʼ��Ϊ-128��
             ��-128����������һ��˼ά��ͼ�ο���������Ȼ����0xFF��������(0...9),
             ��������ϰ�ߡ�
*****************************************************************************/
typedef struct
{
    VOS_INT8                                            cProcessId;     /* Invalid value:-128, the processer id of the next sub frame, value range is 0~2 */
    VOS_INT8                                            cSubPacketId;   /* Invalid value:-128, 0:first time,1:second time,2:third time,3:fouth time */
    VOS_INT8                                            cDataType;      /* Invalid value:-128, it indicates which type data will CSDR_HRPD_SUBFRAME_DATA_TYPE_ENUM_UINT16 end. Possible values are : 0:no data to send, 1:new data, 2:retransmission data, 3:silence duration */
    VOS_INT8                                            cPacketId;      /* Invalid value:-128, value range is 0~9 */
} CTTF_HRPD_MNTN_RTC3MAC_HARQ_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_RTC3MAC_SUBFRAME_HARQ_STRU
 �ṹ˵��  : һ����֡��(4slots)Harq��Ϣ
*****************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_RTC3MAC_HARQ_INFO_STRU   astHarqInfo[CTTF_HRPD_MNTN_NUM_SUBFRAME_INFO_INSTANCES];/* sub-frame information instances */
} CTTF_HRPD_MNTN_RTC3MAC_SUBFRAME_HARQ_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_OM_HRPD_MNTN_RTC3MAC_HARQ_REPORT_STRU
 �ṹ˵��  : HRPD RTC3MAC Harq��Ϣͳ���ϱ�
 ��Ӧ��Ϣ  : ID_CTTF_OM_HRPD_MNTN_HARQ_INFO_IND
 ˵��      : �����ϱ���Ϣ, ��API����ʱ��ָ��ָ���ϱ����ݼ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usPrimId;
    VOS_UINT16                                  usToolId;
    CTTF_HRPD_MNTN_RTC3MAC_SUBFRAME_HARQ_STRU   astHarqData[CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_HARQ];
} CTTF_OM_HRPD_MNTN_RTC3MAC_HARQ_REPORT_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_PER_DEFAULT_RLP_REV_STATISTICS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ϱ��ķ��ͷ����ͳ��
*****************************************************************************/
typedef  struct
{
    VOS_UINT32    ulTotalByteCntHigh;   /* ���͵����ֽ�������32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTotalByteCnt;       /* ���͵����ֽ�������32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCntHigh;     /*����32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCnt;         /*����32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCntHigh;    /*����32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCnt;        /*����32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTotalPacketCnt;     /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewPacketCnt;       /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxPacketCnt;      /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTxNakRequestCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulIgnoredAnNakCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRlpFlushCnt;        /* ��Чֵ: 0xFFFFFFFF */
} CTTF_HRPD_MNTN_PER_DEFAULT_RLP_REV_STATISTICS_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_PER_DEFAULT_RLP_FWD_STATISTICS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ϱ��Ľ��շ����ͳ��
*****************************************************************************/
typedef  struct
{
    VOS_UINT32    ulTotalByteCntHigh;   /* ���յ����ֽ�������32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTotalByteCnt;       /* ���յ����ֽ�������32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCntHigh;     /*����32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCnt;         /*����32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCntHigh;    /*����32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCnt;        /*����32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulDuplicateByteCnt;   /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTotalPacketCnt;     /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewPacketCnt;       /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxPacketCnt;      /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRxedNakRequestCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNakAbortCnt;        /* ��Чֵ: 0xFFFFFFFF */
} CTTF_HRPD_MNTN_PER_DEFAULT_RLP_FWD_STATISTICS_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_PER_DEFAULT_RLP_STATISTICS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Default RLPÿ��ʵ���ͳ����Ϣ
*****************************************************************************/
typedef  struct
{
    VOS_UINT8            ucStreamId;                    /* ����RLPʵ���Ψһ���, ��Чֵ: 0xFF */
    VOS_UINT8            aucReserved[3];                /* �����ֽڣ�������Чֵ��д��ֵΪ0 */
    VOS_UINT32           ulAnResetRequestCnt;           /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32           ulAtResetRequestCnt;           /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32           ulRxAnResetAckCnt;             /* ��Чֵ: 0xFFFFFFFF */
    CTTF_HRPD_MNTN_PER_DEFAULT_RLP_REV_STATISTICS_STRU  stRevInfo;
    CTTF_HRPD_MNTN_PER_DEFAULT_RLP_FWD_STATISTICS_STRU  stFwdInfo;
}CTTF_HRPD_MNTN_PER_DEFAULT_RLP_STATISTICS_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_DEFAULT_RLP_STATISTICS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Default RLP��ͳ����Ϣ
 ��Ӧ��Ϣ  : ID_CTTF_OM_HRPD_MNTN_RLP_STATISTICS_IND
*****************************************************************************/
typedef  struct
{
    VOS_UINT16                                       usPrimId;
    VOS_UINT16                                       usToolId;
    CTTF_HRPD_MNTN_PER_DEFAULT_RLP_STATISTICS_STRU   astRlpEntity[CTTF_HRPD_MNTN_DEFAULT_RLP_MAX_NUM];
} CTTF_OM_HRPD_MNTN_DEFAULT_RLP_STATISTICS_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_PER_MF_RLP_REV_STATISTICS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MFPA����ϱ��ķ��ͷ����ͳ��
*****************************************************************************/
typedef  struct
{
    VOS_UINT32    ulTotalByteCntHigh;   /* ���͵����ֽ�������32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTotalByteCnt;       /* ���͵����ֽ�������32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCntHigh;     /*����32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCnt;         /*����32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCntHigh;    /*����32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCnt;        /*����32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTotalPacketCnt;     /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewPacketCnt;       /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxPacketCnt;      /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTxNakRequestCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulIgnoredAnNakCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRlpFlushCnt;        /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulAnResetRequestCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulAtResetRequestCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRxedAnResetAckCnt;  /* ��Чֵ: 0xFFFFFFFF */
}CTTF_HRPD_MNTN_PER_MF_RLP_REV_STATISTICS_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_PER_MF_RLP_FWD_STATISTICS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MFPA����ϱ��Ľ��շ����ͳ��
*****************************************************************************/
typedef  struct
{
    VOS_UINT32    ulTotalByteCntHigh;  /* ���յ����ֽ�������32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTotalByteCnt;    /* ����32bit�� ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCntHigh;   /*����32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCnt;    /* ����32bit�� ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCntHigh;    /* ����32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCnt;    /* ����32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulDuplicateByteCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTotalPacketCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewPacketCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxPacketCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRxedNakRequestCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNakAbortCnt;   /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulAnResetRequestCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulAtResetRequestCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRxedAnResetAckCnt; /* ��Чֵ: 0xFFFFFFFF */
} CTTF_HRPD_MNTN_PER_MF_RLP_FWD_STATISTICS_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_PER_MF_RLP_STATISTICS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MFPAÿ��RLPʵ���ͳ����Ϣ
*****************************************************************************/
typedef  struct
{
    VOS_UINT8            ucRlpFlowId;   /* ����RLPʵ���Ψһ���, ��Чֵ: 0xFF */
    VOS_UINT8            aucReserved[3]; /* �����ֽڣ�������Чֵ��д��ֵΪ0 */
    CTTF_HRPD_MNTN_PER_MF_RLP_REV_STATISTICS_STRU  stRevInfo;
    CTTF_HRPD_MNTN_PER_MF_RLP_FWD_STATISTICS_STRU  stFwdInfo;
}CTTF_HRPD_MNTN_PER_MF_RLP_STATISTICS_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_MF_RLP_STATISTICS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MFPA�Ŀ�ά�ɲ���Ϣ
 ��Ӧ��Ϣ  : ID_CTTF_OM_HRPD_MNTN_MFPA_RLP_STATISTICS_IND
*****************************************************************************/
typedef  struct
{
    VOS_UINT16                                  usPrimId;
    VOS_UINT16                                  usToolId;
    CTTF_HRPD_MNTN_PER_MF_RLP_STATISTICS_STRU   astRlpEntity[CTTF_HRPD_MNTN_MF_RLP_MAX_NUM];
} CTTF_OM_HRPD_MNTN_MF_RLP_STATISTICS_STRU;


/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_PER_EMF_RLP_REV_STATISTICS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EMPA����ϱ��ķ��ͷ����ͳ��
*****************************************************************************/
typedef  struct
{
    VOS_UINT32    ulSelectRouteACnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulSelectRouteBCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTotalByteCntHigh;   /* ���͵����ֽ�������32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTotalByteCnt;       /* ����32bit�� ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCntHigh;     /* ����32bit�� ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCnt;         /* ����32bit�� ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCntHigh;    /* ����32bit�� ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCnt;        /* ����32bit�� ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTotalPacketCnt;     /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewPacketCnt;       /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxPacketCnt;      /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTxNakReportCnt;     /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulIgnoreAnNakCnt;     /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRlpFlushCnt;        /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulAnResetRequestCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulAtResetRequestCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRxedAnResetAckCnt;  /* ��Чֵ: 0xFFFFFFFF */
} CTTF_HRPD_MNTN_PER_EMF_RLP_REV_STATISTICS_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_PER_EMF_RLP_REV_STATISTICS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EMPA����ϱ��ķ��ͷ����ͳ��
*****************************************************************************/
typedef  struct
{
    VOS_UINT32    ulSelectRouteACnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulSelectRouteBCnt;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTotalByteCntHigh;   /* ���յ����ֽ�������32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTotalByteCnt;       /* ����32bit�� ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCntHigh;     /*����32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCnt;         /* ����32bit�� ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCntHigh;    /*����32bit����Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCnt;        /* ����32bit�� ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulDuplicateByteCnt;   /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulTotalPacketCnt;     /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNewPacketCnt;       /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRetxPacketCnt;      /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRxNakReportCnt;     /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulNakAbortCnt;        /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulAnResetRequestCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulAtResetRequestCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32    ulRxedAnResetAckCnt;  /* ��Чֵ: 0xFFFFFFFF */
} CTTF_HRPD_MNTN_PER_EMF_RLP_FWD_STATISTICS_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_PER_EMF_RLP_STATISTICS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EMPA ÿ��RLPʵ��Ŀ�ά�ɲ���Ϣ
*****************************************************************************/
typedef  struct
{
    VOS_UINT8                                     ucLinkFlowId;    /* ����RLPʵ���Ψһ���, ��Чֵ: 0xFF */
    CTTF_HRPD_PA_MNTN_FLOW_PROTOCOL_ENUM_UINT8    enFlowProtocol;    /* ��֧��FlowProtocolʱ��������Чֵ�ϱ���ֵΪ0xFF */
    CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_ENUM_UINT8   enRouteProtocol;   /* ��֧��RouteProtocolʱ��������Чֵ�ϱ���ֵΪ0xFF */
    VOS_UINT8                                     aucReserved[1];    /* �����ֽڣ�������Чֵ��д��ֵΪ0 */
    CTTF_HRPD_MNTN_PER_EMF_RLP_REV_STATISTICS_STRU   stRevInfo;
    CTTF_HRPD_MNTN_PER_EMF_RLP_FWD_STATISTICS_STRU   stFwdInfo;
} CTTF_HRPD_MNTN_PER_EMF_RLP_STATISTICS_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_EMF_RLP_STATISTICS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EMPA�Ŀ�ά�ɲ���Ϣ
 ��Ӧ��Ϣ  : ID_CTTF_OM_HRPD_MNTN_EMPA_RLP_STATISTICS_IND
*****************************************************************************/
typedef  struct
{
    VOS_UINT16                                   usPrimId;
    VOS_UINT16                                   usToolId;
    CTTF_HRPD_MNTN_PER_EMF_RLP_STATISTICS_STRU   astRlpEntity[CTTF_HRPD_MNTN_EMF_RLP_MAX_NUM];
} CTTF_OM_HRPD_MNTN_EMF_RLP_STATISTICS_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_ACMAC_MNTN_STATISTIC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Acmac��ά�ɲ���Ϣͳ��
*****************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8  enSubProtocol;                   /* C.H1001��subprotocol��ֵ����Чֵ0xFF */
    VOS_UINT8                               aucReserve[3];                   /* �����ֽڣ�������Чֵ��д��ֵΪ0xFF */
    VOS_UINT32                              ulSuccAttemptCnt;                /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulMaxProbeFailCnt;               /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulAdjacentProbeTimerExpiredCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulMailboxFailCnt;                /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulCprocFailCnt;                  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulSndErrorIndCnt;                /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulAccessProbe1Cnt;               /* Access Probe 1�ɹ�����, ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulAccessProbe2Cnt;               /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulAccessProbe3Cnt;               /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulAccessProbe4Cnt;               /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulAccessProbe5Cnt;               /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulAccessProbeAboveCnt;           /* ����Access Probe 5�ųɹ�����, ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt256BitCnt;               /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt512BitCnt;               /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt1024BitCnt;              /* ��Чֵ: 0xFFFFFFFF */
}CTTF_HRPD_ACMAC_MNTN_STATISTIC_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_CCMAC_MNTN_STATISTIC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Ccmac��ά�ɲ���Ϣͳ��
*****************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8  enSubProtocol;      /* C.H1001��subprotocol��ֵ����Чֵ0xFF */
    VOS_UINT8                               aucReserve[3];      /* �����ֽڣ�������Чֵ��д��ֵΪ0xFF */
    VOS_UINT32                              ulPhyPkt128BitCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt256BitCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt512BitCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt1024BitCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulMacLayerPktCnt;   /* ��Чֵ: 0xFFFFFFFF */
}CTTF_HRPD_CCMAC_MNTN_STATISTIC_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_RTCMAC_MNTN_STATISTIC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RTCMAC��ά�ɲ���Ϣͳ��
*****************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8  enSubProtocol;      /* C.H1001��subprotocol��ֵ����Чֵ0xFF */
    CTTF_HRPD_RTCMAC_MNTN_RATE_ENUM_UINT8   enRateLimit;        /* ��Чֵ0xFF  */
    VOS_UINT8                               aucReserve[2];      /* �����ֽڣ�������Чֵ��д��ֵΪ0xFF */
    VOS_UINT32                              ulPhyPkt128BitCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt256BitCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt512BitCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt768BitCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt1024BitCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt1536BitCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt2048BitCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt3072BitCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt4096BitCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt6144BitCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt8192BitCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt12288BitCnt;/* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulSndErrorIndCnt;   /* ��Чֵ: 0xFFFFFFFF */
} CTTF_HRPD_RTCMAC_MNTN_STATISTIC_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_FTCMAC_MNTN_STATISTIC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : FTCMAC��ά�ɲ���Ϣͳ��
*****************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8  enSubProtocol;      /* C.H1001��subprotocol��ֵ����Чֵ0xFF */
    VOS_UINT8                               aucReserve[3];      /* �����ֽڣ�������Чֵ��д��ֵΪ0xFF */
    VOS_UINT32                              ulPhyPkt128BitCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt256BitCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt512BitCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt1024BitCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt2048BitCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt3072BitCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt4096BitCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt5120BitCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulTotPhyPktCnt;     /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulTotMacLayPktCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulTotSingUserPktCnt;  /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulTotMultiUserPktCnt; /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulMaxSecLayPktNum;    /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulTotalMacPacketBytes;      /* MAC Packet Byte Size,������2bits MAC trailer����Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulTotMyAtMacPayloadBytes;   /* ��Чֵ: 0xFFFFFFFF */
    VOS_UINT32                              ulTotOtherAtMacPayloadBytes;/* ��Чֵ: 0xFFFFFFFF */
}CTTF_HRPD_FTCMAC_MNTN_STATISTIC_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_OM_HRPD_MAC_MNTN_STATISTIC_STRU
 �ṹ˵��  : HRPD MAC ��Ϣͳ���ϱ�
 ��Ӧ��Ϣ  : ID_CTTF_OM_HRPD_MNTN_MAC_PROTOCOL_STATISTICS_IND
 ˵��      : �����ϱ���Ϣ, ��API����ʱ��ָ��ָ���ϱ����ݼ���
*****************************************************************************/
typedef  struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usToolId;

    CTTF_HRPD_ACMAC_MNTN_STATISTIC_STRU     stAcMac;
    CTTF_HRPD_CCMAC_MNTN_STATISTIC_STRU     stCcMac;
    CTTF_HRPD_RTCMAC_MNTN_STATISTIC_STRU    stRtcMac;
    CTTF_HRPD_FTCMAC_MNTN_STATISTIC_STRU    stFtcMac;
} CTTF_OM_HRPD_MAC_MNTN_STATISTIC_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_CC_MAC_PROTOCL_STATE_STRU
 * Description : DCC��ECCЭ��״̬�ṹ
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                  enSubProtocol;      /*��Чֵ: BUTT */
    CTTF_HRPD_MNTN_CC_STATE_ENUM_UINT8                      enState;            /* ��Чֵ: BUTT */
    VOS_UINT8                                               aucReserve[2];      /* �����ֽڣ�������Чֵ��д��ֵΪ0 */
}CTTF_HRPD_MNTN_MODULE_CC_MAC_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_AC_MAC_PROTOCL_STATE_STRU
 * Description : DAC��EACЭ��״̬�ṹ
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                  enSubProtocol;      /*��Чֵ: BUTT */
    CTTF_HRPD_MNTN_AC_STATE_ENUM_UINT8                      enState;            /* ��Чֵ: BUTT */
    VOS_UINT8                                               aucReserve[2];      /* �����ֽڣ�������Чֵ��д��ֵΪ0 */
}CTTF_HRPD_MNTN_MODULE_AC_MAC_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_FTC_MAC_PROTOCL_STATE_STRU
 * Description : DFTC��EFTCЭ��״̬�ṹ
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                  enSubProtocol;      /*��Чֵ: BUTT */
    CTTF_HRPD_MNTN_FTC_STATE_ENUM_UINT8                     enState;            /* ��Чֵ: BUTT */
    VOS_UINT8                                               aucReserve[2];      /* �����ֽڣ�������Чֵ��д��ֵΪ0 */
}CTTF_HRPD_MNTN_MODULE_FTC_MAC_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_RTC_MAC_PROTOCL_STATE_STRU
 * Description : DRTC��ST3 RTCЭ��״̬�ṹ
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;  /*��Чֵ: BUTT */
    CTTF_HRPD_MNTN_RTC_STATE_ENUM_UINT8                         enState;        /* ��Чֵ: BUTT */
    VOS_UINT8                                                   aucReserve[2];  /* �����ֽڣ�������Чֵ��д��ֵΪ0 */
}CTTF_HRPD_MNTN_MODULE_RTC_MAC_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_AUTHENTICATION_PROTOCL_STATE_STRU
 * Description : ��ȨЭ��״̬�ṹ
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;  /*��Чֵ: BUTT */
    CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_ENUM_UINT8     enState;        /* ��Чֵ: BUTT */
    VOS_UINT8                                                   aucReserve[2];  /* �����ֽڣ�������Чֵ��д��ֵΪ0 */
}CTTF_HRPD_MNTN_MODULE_AUTHENTICATION_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_ENCRYPTION_PROTOCL_STATE_STRU
 * Description : ����Э��״̬�ṹ
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;  /*��Чֵ: BUTT */
    CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_ENUM_UINT8     enState;        /* ��Чֵ: BUTT */
    VOS_UINT8                                                   aucReserve[2];  /* �����ֽڣ�������Чֵ��д��ֵΪ0 */
}CTTF_HRPD_MNTN_MODULE_ENCRYPTION_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_SECURITY_PROTOCL_STATE_STRU
 * Description : ��ȫЭ��״̬�ṹ
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;  /*��Чֵ: BUTT */
    CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_ENUM_UINT8     enState;        /* ��Чֵ: BUTT */
    VOS_UINT8                                                   aucReserve[2];  /* �����ֽڣ�������Чֵ��д��ֵΪ0 */
}CTTF_HRPD_MNTN_MODULE_SECURITY_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_STREAM_FLOW_CTRL_PROTOCL_STATE_STRU
 * Description : ����Э��״̬�ṹ
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;  /*��Чֵ: BUTT */
    CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_PROTOCOL_STATE_ENUM_UINT8   enState;        /* ��Чֵ: BUTT */
    VOS_UINT8                                                   aucReserve[2];  /* �����ֽڣ�������Чֵ��д��ֵΪ0 */
}CTTF_HRPD_MNTN_MODULE_STREAM_FLOW_CTRL_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_STREAM_APP_PROTOCL_STATE_STRU
 * Description : ��Ӧ��Э��״̬�ṹ
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;  /*��Чֵ: BUTT */
    CTTF_HRPD_MNTN_STREAM_APP_PROTOCOL_STATE_ENUM_UINT8         enState;        /* ��Чֵ: BUTT */
    VOS_UINT8                                                   aucReserve[2];  /* �����ֽڣ�������Чֵ��д��ֵΪ0 */
}CTTF_HRPD_MNTN_MODULE_STREAM_APP_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_SNP_UP_TX_STATE_STRU
 * Description : SNPЭ��״̬�ṹ
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;  /*��Чֵ: BUTT */
    CTTF_HRPD_MNTN_SNP_UP_TX_STATE_ENUM_UINT8                   enState;        /* ��Чֵ: BUTT */
    VOS_UINT8                                                   aucReserve[2];  /* �����ֽڣ�������Чֵ��д��ֵΪ0 */
}CTTF_HRPD_MNTN_MODULE_SNP_UP_TX_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_PROTOCOL_STATE_STRU
 * Description : ģ��Э��״̬�ṹ
 * ��Ӧ��Ϣ  : ID_CTTF_OM_HRPD_MNTN_MODULE_PROTOCOL_STATE_IND
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                                  usPrimId;
    VOS_UINT16                                                  usToolId;

    CTTF_HRPD_MNTN_MODULE_CC_MAC_PROTOCL_STATE_STRU             stCcMac;
    CTTF_HRPD_MNTN_MODULE_AC_MAC_PROTOCL_STATE_STRU             stAcMac;
    CTTF_HRPD_MNTN_MODULE_FTC_MAC_PROTOCL_STATE_STRU            stFtcMac;
    CTTF_HRPD_MNTN_MODULE_RTC_MAC_PROTOCL_STATE_STRU            stRtcMac;
    CTTF_HRPD_MNTN_MODULE_AUTHENTICATION_PROTOCL_STATE_STRU     stAuth;
    CTTF_HRPD_MNTN_MODULE_ENCRYPTION_PROTOCL_STATE_STRU         stEncryption;
    CTTF_HRPD_MNTN_MODULE_SECURITY_PROTOCL_STATE_STRU           stSecurity;
    CTTF_HRPD_MNTN_MODULE_STREAM_FLOW_CTRL_PROTOCL_STATE_STRU   stStream0;
    CTTF_HRPD_MNTN_MODULE_STREAM_FLOW_CTRL_PROTOCL_STATE_STRU   stStream1;
    CTTF_HRPD_MNTN_MODULE_STREAM_FLOW_CTRL_PROTOCL_STATE_STRU   stStream2;
    CTTF_HRPD_MNTN_MODULE_STREAM_FLOW_CTRL_PROTOCL_STATE_STRU   stStream3;
    CTTF_HRPD_MNTN_MODULE_STREAM_APP_PROTOCL_STATE_STRU         stStream0App;
    CTTF_HRPD_MNTN_MODULE_STREAM_APP_PROTOCL_STATE_STRU         stStream1App;
    CTTF_HRPD_MNTN_MODULE_STREAM_APP_PROTOCL_STATE_STRU         stStream2App;
    CTTF_HRPD_MNTN_MODULE_STREAM_APP_PROTOCL_STATE_STRU         stStream3App;
    CTTF_HRPD_MNTN_MODULE_SNP_UP_TX_STATE_STRU                  stSnpUplinkTx;
}CTTF_OM_HRPD_MNTN_MODULE_PROTOCOL_STATE_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_RTC3MAC_ACK_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RTCά���ϱ���ACK��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32      aulACKsNum[CTTF_HRPD_MAC_TRANS_MODE_BUTT];                                          /* ulInterlace[interlacenumber]������֮��,��Ӧ��ͬ����ģʽ */
    VOS_UINT32      aulPktNumOnInterlace[CTTF_HRPD_MNTN_RTC3MAC_INTERLACE_MAX_NUM][CTTF_HRPD_MAC_TRANS_MODE_BUTT];  /* ��Ӧ��֯���յ���ACK���������ۼ�ֵ����Ӧ��ͬ�Ĵ���ģʽ */
}CTTF_HRPD_MNTN_RTC3MAC_ACK_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_HRPD_MNTN_RTC3MAC_ACK_INFO_STATIS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RTC Reverse Link Metrics ͳ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulGoodPacketNumSum;                                         /* ulGoodPacketNum[CTTF_HRPD_RTC3MAC_TRANS_MODE_BUTT]��� */
    VOS_UINT32                              aulGoodPacketNum[CTTF_HRPD_MAC_TRANS_MODE_BUTT];            /* �ܷ��ͳɹ���Packet������ֵ����ACK�ĸ��� */
    VOS_UINT32                              ulAvgPacketTerminationSum;                                  /* ulAvgPacketTermination[CTTF_HRPD_RTC3MAC_TRANS_MODE_BUTT]��� */
    VOS_UINT32                              aulAvgPacketTermination[CTTF_HRPD_MAC_TRANS_MODE_BUTT]; /* ����֡Ϊ��λ����Packetƽ�����͵���֡�� */
    VOS_UINT32                              ulTotlPktTxTimeSum;                                         /* ulTotlPktTxTime[CTTF_HRPD_RTC3MAC_TRANS_MODE_BUTT]��� */
    VOS_UINT32                              aulTotlPktTxTime[CTTF_HRPD_MAC_TRANS_MODE_BUTT];            /* ���ݰ��ܵķ���ʱ�䣬��msΪ��λ */
}CTTF_HRPD_MNTN_RTC3MAC_ACK_INFO_STATIS_STRU;

/*****************************************************************************
 �ṹ��    : CTTF_OM_HRPD_MNTN_RTC3MAC_ACK_INFO_REPORT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RTC Reverse Link Metrics��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usPrimId;
    VOS_UINT16                                      usToolId;

    CTTF_HRPD_MNTN_RTC3MAC_ACK_INFO_STRU            astRtc3MacAckInfo[CTTF_HRPD_MNTN_RTC3MAC_PS_BUTT][CSDR_HARQ_MNTN_SUBPACKET_BUTT];   /* ÿ��PS���Ͷ�Ӧ��ACK info, PS0��Ӧ��λ�ò����õ�������λ���������"����PS���͵�ACK info֮��" */
    CTTF_HRPD_MNTN_RTC3MAC_ACK_INFO_STATIS_STRU     astRtc3MacAckInfoStatis[CTTF_HRPD_MNTN_RTC3MAC_PS_BUTT];    /* ÿ��PS���Ͷ�Ӧ��ACKͳ����Ϣ, PS0��Ӧ��λ�ò����õ�������λ���������"����PS���Ͷ�Ӧ��ACKͳ����Ϣ֮��" */
    VOS_UINT32                                      ulTotalParqNAKsNum;                                     /* �յ�PARQ NAK�ĸ������ۼ�ֵ�������ִ���ģʽҲ������PS���� */
    VOS_UINT32                                      ulTotalPacketSentNum;                                   /* �ܷ��͵�Packet����������ACK��PARQ�е�NAK�������ִ���ģʽҲ������PS���� */
    VOS_UINT32                                      ulTotalPer;                                             /* ��ʾ�е�����ʣ�����ֵ�Ѿ��Ŵ�100������ʾ��ʱ����%����ʽ��ʾ */
}CTTF_OM_HRPD_MNTN_RTC3MAC_ACK_INFO_REPORT_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#ifndef COMM_ITT
extern VOS_VOID TTF_TraceModuleSet(VOS_UINT8 *paucModuleId);
#endif
extern VOS_VOID *TTF_FilterMsgCallBack(MsgBlock *pMsg);
extern VOS_VOID WTTF_TraceModuleCfgReq(VOS_VOID* pMsg);
extern VOS_VOID WTTF_MAC_R99MailBox_ReadForIpcHalt(VOS_VOID);
extern VOS_VOID WTTF_R99MailboxInitForCbt(VOS_VOID);


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TtfOamInterface.h */

