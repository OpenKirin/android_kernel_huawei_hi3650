/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_encap_frame_test.c
  �� �� ��   : ����
  ��    ��   : z00260280
  ��������   : 2014��1��27��
  ����޸�   :
  ��������   : оƬ��֤֡������֡������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "frw_ext_if.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "mac_regdomain.h"
#include "dmac_ext_if.h"
#include "dmac_vap.h"
#include "dmac_main.h"
#include "dmac_frame_filter_test.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_FRAME_FILTER_TEST_C

#ifdef _PRE_WLAN_CHIP_TEST
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define DMAC_TEST_BROADCAST 1
#define DMAC_TEST_MULTICAST 2
#define DMAC_TEST_UNICAST   3

/*****************************************************************************
  3 �ڲ���������
*****************************************************************************/
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : dmac_test_encap_ctl_bmucst
 ��������  : ��װ�鲥�㲥�鲥����֡
 �������  : pst_dmac_vap: DMAC VAP

             ucbmcst:��ʶ�㲥/�鲥/����
 �������  : uc_buffer: buffer��ʼ��ַ
 �� �� ֵ  : ��װ���֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_test_encap_ctl_bmucst(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buffer, oal_int8 ucbmucst, oal_uint8 *puc_mac)
{
    oal_uint8        auc_mcst_addr[6] = {0x01, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c}; /* �鲥��ַ */
    oal_uint8       *puc_origin       = puc_buffer;
    oal_uint16       us_bar_ctl =0;
    /*************************************************************************/
    /*                        control Frame Format                           */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|AID     |RA    |TA      |FCS|                          */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6     |6       |4    |                        */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                            ����֡ͷ                                   */
    /*************************************************************************/
    /* ֡�����ֶ�ȫΪ0������type��subtype */
    mac_hdr_set_frame_control(puc_buffer, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_CTL| WLAN_FC0_SUBTYPE_BAR);

    /* ����aidΪ0 */
    puc_buffer[2] = (oal_uint16)0x00;

    /* ���õ�ַ1���㲥/�鲥 ��ַ */
    switch(ucbmucst)
    {
        case DMAC_TEST_BROADCAST:
        {
            oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR1_OFFSET, BROADCAST_MACADDR);
            break;
        }
        case DMAC_TEST_MULTICAST:
        {
            oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR1_OFFSET, auc_mcst_addr);
            break;
        }
        case DMAC_TEST_UNICAST:
        {
            oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR1_OFFSET, puc_mac);
            break;
        }
        default:
        {
            break;
        }
    }

    /* ���õ�ַ2Ϊ�Լ���MAC��ַ */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR2_OFFSET, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* BAR Control field */
    us_bar_ctl = (oal_uint16)(0 << 12);

    /* BAR-Ack Policy is set to Normal Ack */
    us_bar_ctl &= ~BIT0;


    us_bar_ctl |= BIT2;
    us_bar_ctl &= ~BIT1;

    puc_buffer[16] = us_bar_ctl & 0xFF;
    puc_buffer[17] = (us_bar_ctl >> 8) & 0xFF;
    /* Sequence number */
    puc_buffer[18] = 0;
    puc_buffer[19] = 0;
    /* puc_buffer += MAC_80211_CTL_HEADER_LEN; */
    puc_buffer += 20;
    return (oal_uint16)(puc_buffer - puc_origin);
}



/*****************************************************************************
 �� �� ��  : dmac_test_encap_ctl_bcst
 ��������  : ��㲥����֡
 �������  :vapָ��
            puc_param �������
 �������  : puc_buff:������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_test_encap_ctl_bcst(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buff, oal_uint8 *puc_param, oal_uint32 ul_param_len)
{
    mac_cfg_send_frame_param_stru     *pst_param = (mac_cfg_send_frame_param_stru  *)puc_param;
    return dmac_test_encap_ctl_bmucst(pst_mac_vap,
                                      puc_buff,
                                      DMAC_TEST_BROADCAST,
                                      pst_param->auc_mac_ra);
}

/*****************************************************************************
 �� �� ��  : dmac_test_encap_cts_ucst
 ��������  : ���鲥����֡
 �������  : vapָ��
             puc_param �������
 �������  : puc_buff:������
 �� �� ֵ  : ֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_test_encap_ctl_mcst(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buff, oal_uint8 *puc_param, oal_uint32 ul_param_len)
{
    mac_cfg_send_frame_param_stru     *pst_param = (mac_cfg_send_frame_param_stru  *)puc_param;
    return dmac_test_encap_ctl_bmucst(pst_mac_vap,
                                      puc_buff,
                                      DMAC_TEST_MULTICAST,
                                      pst_param->auc_mac_ra);
}

/*****************************************************************************
 �� �� ��  : dmac_test_encap_cts_ucst
 ��������  : ���CTS/RTS/ACK�ĵ�������֡
 �������  : vapָ��
             puc_param �������
 �������  : puc_buff:������
 �� �� ֵ  : ֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_test_encap_ctl_ucst(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buff, oal_uint8 *puc_param, oal_uint32 ul_param_len)
{
    mac_cfg_send_frame_param_stru     *pst_param = (mac_cfg_send_frame_param_stru  *)puc_param;
    return dmac_test_encap_ctl_bmucst(pst_mac_vap,
                                      puc_buff,
                                      DMAC_TEST_UNICAST,
                                      pst_param->auc_mac_ra);
}


/*****************************************************************************
 �� �� ��  : dmac_test_encap_ctl_cts_ack
 ��������  : ��װCTS/ACK
 �������  : pst_dmac_vap: DMAC VAP
             puc_mac: RA
 �������  : uc_buffer: buffer��ʼ��ַ
 �� �� ֵ  : ��װ���֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_test_encap_ctl_cts_ack(oal_uint8 *puc_buffer, oal_uint8 *puc_mac, oal_int16 us_subtype)
{
    oal_uint8       *puc_origin = puc_buffer;

    /*************************************************************************/
    /*                        control Frame Format                           */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration  |RA    |FCS|                          */
    /* --------------------------------------------------------------------  */
    /* | 2           |2         |6     |4  |                        */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                        ����֡ͷ                                      */
    /*************************************************************************/

    /* ֡�����ֶ�ȫΪ0������type��subtype */
    mac_hdr_set_frame_control(puc_buffer, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_CTL| us_subtype);

    /* ����durationΪ0 */
    puc_buffer[2] = (oal_uint16)0x00;

    /* ���õ�ַ1 */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR1_OFFSET, puc_mac);

    puc_buffer += 10;

    return (oal_uint16)(puc_buffer - puc_origin);
}

/*****************************************************************************
 �� �� ��  : dmac_test_encap_ack_ucst
 ��������  : ��ACK��������֡
 �������  : vapָ��
             puc_param �������
 �������  : puc_buff:������
 �� �� ֵ  : ֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_test_encap_ack_ucst(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buff, oal_uint8 *puc_param, oal_uint32 ul_param_len)
{
    mac_cfg_send_frame_param_stru     *pst_param = (mac_cfg_send_frame_param_stru  *)puc_param;
    return dmac_test_encap_ctl_cts_ack(puc_buff,  pst_param->auc_mac_ra,WLAN_FC0_SUBTYPE_ACK);
}


/*****************************************************************************
 �� �� ��  : dmac_test_encap_cts_ucst
 ��������  : ��CTS��������֡
 �������  : vapָ��
             puc_param �������
 �������  : puc_buff:������
 �� �� ֵ  : ֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_test_encap_cts_ucst(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buff, oal_uint8 *puc_param, oal_uint32 ul_param_len)
{
    mac_cfg_send_frame_param_stru     *pst_param = (mac_cfg_send_frame_param_stru  *)puc_param;
    return dmac_test_encap_ctl_cts_ack(puc_buff,  pst_param->auc_mac_ra,WLAN_FC0_SUBTYPE_CTS);
}


/*****************************************************************************
 �� �� ��  : dmac_test_encap_ctl_rts
 ��������  : ��װRTS
 �������  : pst_dmac_vap: DMAC VAP
             puc_mac: RA
 �������  : uc_buffer: buffer��ʼ��ַ
 �� �� ֵ  : ��װ���֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_test_encap_ctl_rts(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buffer, oal_uint8 *puc_mac)
{
    oal_uint8       *puc_origin = puc_buffer;


    /*************************************************************************/
    /*                        control Frame Format                           */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration  |RA    |TA      |FCS|                          */
    /* --------------------------------------------------------------------  */
    /* | 2           |2         |6     |6       |4    |                        */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                        ����֡ͷ                                      */
    /*************************************************************************/
    /* ֡�����ֶ�ȫΪ0������type��subtype */
    mac_hdr_set_frame_control(puc_buffer, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_CTL| WLAN_FC0_SUBTYPE_RTS);

    /* ����aidΪ0 */
    puc_buffer[2] = (oal_uint16)0x00;

    /* ���õ�ַ1 */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR1_OFFSET, puc_mac);

    /* ���õ�ַ2Ϊ�Լ���MAC��ַ */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR2_OFFSET, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    puc_buffer += MAC_80211_CTL_HEADER_LEN;

    return (oal_uint16)(puc_buffer - puc_origin);
}


/*****************************************************************************
 �� �� ��  : dmac_test_encap_rts_ucst
 ��������  : ��RTS��������֡
 �������  : vapָ��
             puc_param �������
 �������  : puc_buff:������
 �� �� ֵ  : ֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_test_encap_rts_ucst(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buff, oal_uint8 *puc_param, oal_uint32 ul_param_len)
{
    mac_cfg_send_frame_param_stru     *pst_param = (mac_cfg_send_frame_param_stru  *)puc_param;
    return dmac_test_encap_ctl_rts(pst_mac_vap, puc_buff, pst_param->auc_mac_ra);
}

/*****************************************************************************
 �� �� ��  : dmac_test_mgmt_encap_asoc_rsp
 ��������  : �������Ӧ֡����Ϊ����֡
 �������  : vapָ��
             puc_param �������
 �������  : puc_buff:������
 �� �� ֵ  : ֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_test_mgmt_encap_asoc_rsp(
                mac_vap_stru                   *pst_mac_ap,
                oal_uint8                      *puc_sta_addr,
                oal_uint8                      *puc_ta_addr,
                oal_uint16                      us_assoc_id,
                oal_uint8                      *puc_asoc_rsp,
                oal_uint16                      us_type)
{
    oal_uint32        us_asoc_rsp_len       = 0;
    /* mac_device_stru  *pst_mac_device; */
    oal_uint8        *puc_asoc_rsp_original;


    if ((OAL_PTR_NULL == pst_mac_ap) || (OAL_PTR_NULL == puc_sta_addr) || (OAL_PTR_NULL == puc_asoc_rsp))
    {
        OAM_ERROR_LOG3(0, OAM_SF_FRAME_FILTER,
                          "{dmac_test_mgmt_encap_asoc_rsp::pst_mac_ap=%u, puc_data=%u, puc_asoc_req=%u }\r\n",
                            pst_mac_ap,
                            puc_sta_addr,
                            puc_asoc_rsp);
        return us_asoc_rsp_len;
    }

    /* ������ʼ��ַ��������㳤��*/
    puc_asoc_rsp_original = puc_asoc_rsp;
    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                        ����֡ͷ                                      */
    /*************************************************************************/
    /* ���� Frame Control field */
    mac_hdr_set_frame_control(puc_asoc_rsp, us_type);

    /* ���� DA address1: STA MAC��ַ*/
    oal_set_mac_addr(puc_asoc_rsp + WLAN_HDR_ADDR1_OFFSET, puc_sta_addr);

    /* ���� SA address2: dot11MACAddress */
    /* oal_set_mac_addr(puc_asoc_rsp + WLAN_HDR_ADDR2_OFFSET, pst_mac_ap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID); */
    oal_set_mac_addr(puc_asoc_rsp + WLAN_HDR_ADDR2_OFFSET, puc_ta_addr);

    /* ���� DA address3: AP MAC��ַ (BSSID)*/
    oal_set_mac_addr(puc_asoc_rsp + WLAN_HDR_ADDR3_OFFSET, pst_mac_ap->auc_bssid);

    puc_asoc_rsp += MAC_80211_FRAME_LEN;


#if 0
    puc_asoc_rsp[0] = MAC_EID_SSID;
    /* puc_buffer[1] = (oal_uint8)OAL_STRLEN(pst_mac_vap->auc_bssid); */
    puc_asoc_rsp[1] = OAL_MAC_ADDR_LEN;
    oal_memcopy(&(puc_asoc_rsp[2]), pst_mac_ap->auc_bssid, puc_asoc_rsp[1]);
    puc_asoc_rsp += MAC_IE_HDR_LEN + puc_asoc_rsp[1];  /* ƫ��bufferָ����һ��ie */
#endif
    /* ���� capability information field */
    mac_set_cap_info_ap((oal_void *)pst_mac_ap, puc_asoc_rsp);
    puc_asoc_rsp += MAC_CAP_INFO_LEN;


    /* ���� Status Code */
    mac_set_status_code_ie(puc_asoc_rsp, MAC_SUCCESSFUL_STATUSCODE);
    puc_asoc_rsp += MAC_STATUS_CODE_LEN;

    /* ���� Association ID,��׮ */
    mac_set_aid_ie(puc_asoc_rsp, 0x01);
    puc_asoc_rsp += MAC_AID_LEN;

    /* ����ie */
    puc_asoc_rsp[0] = MAC_EID_SSID;
    puc_asoc_rsp[1] = OAL_MAC_ADDR_LEN;
    oal_memcopy(&(puc_asoc_rsp[2]), pst_mac_ap->auc_bssid, puc_asoc_rsp[1]);
    puc_asoc_rsp += MAC_IE_HDR_LEN + puc_asoc_rsp[1];  /* ƫ��bufferָ����һ��ie */
    us_asoc_rsp_len = (oal_uint32)(puc_asoc_rsp - puc_asoc_rsp_original);
    return us_asoc_rsp_len;
}

/*****************************************************************************
 �� �� ��  : dmac_test_encap_mgmt_bmcst
 ��������  : ��㲥/�鲥 ����֡
 �������  : vapָ��
             puc_param �������
 �������  : puc_buff:������
 �� �� ֵ  : ֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint16  dmac_test_encap_mgmt_bmcst(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buffer, oal_int8 ucbmcst)
{
    oal_uint8        auc_mcst_addr[6] = {0x01, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc}; /* �鲥��ַ */
    oal_uint8       *puc_origin       = puc_buffer;

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                              ����֡ͷ                                  */
    /*************************************************************************/
    /* ֡�����ֶ�ȫΪ0������type��subtype */
    mac_hdr_set_frame_control(puc_buffer, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_PROBE_REQ);

    /* ���÷�Ƭ���Ϊ0 */
    mac_hdr_set_fragment_number(puc_buffer, 0);

    /* ���õ�ַ1���㲥��ַ */
    if(DMAC_TEST_BROADCAST == ucbmcst)
    {
        oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR1_OFFSET, BROADCAST_MACADDR);
    }
    else
    {
        oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR1_OFFSET, auc_mcst_addr);
    }

    /* ���õ�ַ2Ϊ�Լ���MAC��ַ */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR2_OFFSET, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* ��ַ3 bssid */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR3_OFFSET, pst_mac_vap->auc_bssid);

    puc_buffer += MAC_80211_FRAME_LEN;

    puc_buffer[0] = MAC_EID_SSID;
    /* puc_buffer[1] = (oal_uint8)OAL_STRLEN(pst_mac_vap->auc_bssid); */
    puc_buffer[1] = OAL_MAC_ADDR_LEN;
    oal_memcopy(&(puc_buffer[2]), pst_mac_vap->auc_bssid, puc_buffer[1]);
    puc_buffer += MAC_IE_HDR_LEN + puc_buffer[1];  /* ƫ��bufferָ����һ��ie */

    return (oal_uint16)(puc_buffer - puc_origin);
}

/*****************************************************************************
 �� �� ��  : dmac_test_encap_mgmt_bcst
 ��������  : ��㲥����֡
 �������  : vapָ��
             puc_param �������
 �������  : puc_buff:������
 �� �� ֵ  : ֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_test_encap_mgmt_bcst(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buff, oal_uint8 *puc_param, oal_uint32 ul_param_len)
{
    return dmac_test_encap_mgmt_bmcst(pst_mac_vap,
                                            puc_buff,
                                            DMAC_TEST_BROADCAST);
}

/*****************************************************************************
 �� �� ��  : dmac_test_encap_mgmt_mcst
 ��������  : ���鲥����֡
 �������  : vapָ��
             puc_param �������
 �������  : puc_buff:������
 �� �� ֵ  : ֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_test_encap_mgmt_mcst(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buff, oal_uint8 *puc_param, oal_uint32 ul_param_len)
{
    return dmac_test_encap_mgmt_bmcst(pst_mac_vap,
                                            puc_buff,
                                            DMAC_TEST_MULTICAST);
}


/*****************************************************************************
 �� �� ��  : dmac_test_encap_mgmt_atim
 ��������  : ��ATIM����֡
 �������  : vapָ��
             puc_param �������
 �������  : puc_buff:������
 �� �� ֵ  : ֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_test_encap_mgmt_atim(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buff, oal_uint8 *puc_param, oal_uint32 ul_param_len)
{
    oal_uint8                           *puc_origin = puc_buff;
    mac_cfg_send_frame_param_stru       *pst_param  = (mac_cfg_send_frame_param_stru  *)puc_param;

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                        ����֡ͷ                                      */
    /*************************************************************************/
    /* ֡�����ֶ�ȫΪ0������type��subtype */
    mac_hdr_set_frame_control(puc_buff, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_ATIM);

    /* ���÷�Ƭ���Ϊ0 */
    mac_hdr_set_fragment_number(puc_buff, 0);

    /* ���õ�ַ1*/
    oal_set_mac_addr(puc_buff + WLAN_HDR_ADDR1_OFFSET, pst_param->auc_mac_ra);

    /* ���õ�ַ2Ϊ�Լ���MAC��ַ */
    oal_set_mac_addr(puc_buff + WLAN_HDR_ADDR2_OFFSET, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* ��ַ3 bssid */
    oal_set_mac_addr(puc_buff + WLAN_HDR_ADDR3_OFFSET, pst_mac_vap->auc_bssid);

    /* frame body ΪNULL */
    puc_buff += MAC_80211_FRAME_LEN;

    return (oal_uint16)(puc_buff - puc_origin);
}


/*****************************************************************************
 �� �� ��  : dmac_test_encap_mgmt_ucst
 ��������  : �������֡
 �������  : vapָ��
             puc_param �������
 �������  : puc_buff:������
 �� �� ֵ  : ֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_test_encap_mgmt_ucst(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buff, oal_uint8 *puc_param, oal_uint32 ul_param_len)
{
    mac_cfg_send_frame_param_stru     *pst_param = (mac_cfg_send_frame_param_stru  *)puc_param;
    return dmac_test_mgmt_encap_asoc_rsp(pst_mac_vap,
                                 pst_param->auc_mac_ra,
                                 pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID,
                                 0,
                                 puc_buff,
                                 WLAN_FC0_SUBTYPE_ASSOC_RSP);
}

/*****************************************************************************
 �� �� ��  : dmac_test_encap_mgmt_ucst
 ��������  : �������֡,RA��ַ��TA��ַһ��
 �������  : vapָ��
             puc_param �������
 �������  : puc_buff:������
 �� �� ֵ  : ֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_test_encap_mgmt_ucst_ra_equal_ta(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buff, oal_uint8 *puc_param, oal_uint32 ul_param_len)
{
    mac_cfg_send_frame_param_stru     *pst_param = (mac_cfg_send_frame_param_stru  *)puc_param;
    return dmac_test_mgmt_encap_asoc_rsp(pst_mac_vap,
                                 pst_param->auc_mac_ra,
                                 pst_param->auc_mac_ra,
                                 0,
                                 puc_buff,
                                 WLAN_FC0_SUBTYPE_ASSOC_RSP);
}

/*****************************************************************************
 �� �� ��  : dmac_test_encap_ba
 ��������  : ��װBA,��������delayed ba
 �������  : pst_dmac_vap: DMAC VAP
             puc_mac: RA
 �������  : uc_buffer: buffer��ʼ��ַ
 �� �� ֵ  : ��װ���֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_test_encap_ba(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buff, oal_uint8 *puc_param, oal_uint32 ul_param_len)
{
    oal_uint16       us_ba_ctl =0;
    mac_cfg_send_frame_param_stru     *pst_param = (mac_cfg_send_frame_param_stru  *)puc_param;
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_buff) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG3(0, OAM_SF_FRAME_FILTER,
                          "{dmac_test_encap_ba::pst_mac_vap=%u, puc_data=%u, puc_param=%u }\r\n",
                            pst_mac_vap,
                            puc_buff,
                            puc_param);
        return 0;
    }

    /*************************************************************************/
    /*                     BlockAck  Frame Format                             */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|RA|TA|BA Control|BA Info              |FCS|  */
    /* |             |        |  |  |          |                     |   |  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |2         |var                  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*  ��׮����subtypeΪBA */
    mac_hdr_set_frame_control(puc_buff, (oal_uint16)WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_CTL | WLAN_FC0_SUBTYPE_BA);

    /* ����RA */
    oal_set_mac_addr(puc_buff + 4, pst_param->auc_mac_ra);

    /* ����TA ,BA control��BA Info����*/
    oal_set_mac_addr(puc_buff + 10, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    /* BAR Control field */
    us_ba_ctl = (oal_uint16)(0 << 12);

    /* BA Policy is set to Normal Ack */
    us_ba_ctl &= ~BIT0;
    /* ��multi tid */
    us_ba_ctl &= ~BIT1;
    /* compressed bitmap */
    us_ba_ctl |= BIT2;
    /* BA control */
    puc_buff[16] = us_ba_ctl & 0xFF;
    puc_buff[17] = (us_ba_ctl >> 8) & 0xFF;

    /* BA info,2+8�ܹ�10���ֽڣ����Ĭ��Ϊ0 */
    return MAC_80211_CTL_HEADER_LEN + 12;
}

/*****************************************************************************
 �� �� ��  : dmac_test_encap_cf_end_ucst
 ��������  : ��װCF-END
 �������  : pst_dmac_vap: DMAC VAP
             puc_mac: RA
 �������  : uc_buffer: buffer��ʼ��ַ
 �� �� ֵ  : ��װ���֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_test_encap_cf_end_ucst(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buff, oal_uint8 *puc_param, oal_uint32 ul_param_len)
{
    mac_cfg_send_frame_param_stru     *pst_param = (mac_cfg_send_frame_param_stru  *)puc_param;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_buff) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG3(0, OAM_SF_FRAME_FILTER,
                          "{dmac_test_encap_cf_end_ucst::pst_mac_vap=%u, puc_buff=%u, puc_param=%u }\r\n",
                            pst_mac_vap,
                            puc_buff,
                            puc_param);
        return 0;
    }

    /*************************************************************************/
    /*                        control Frame Format                           */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration  |RA    |TA    |FCS|                          */
    /* --------------------------------------------------------------------  */
    /* | 2           |2         |6     |6     |4  |                          */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*  ��׮����subtypeΪCF-End */
    mac_hdr_set_frame_control(puc_buff, (oal_uint16)WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_CTL | WLAN_FC0_SUBTYPE_CF_END);

    /* ����RA */
    oal_set_mac_addr(puc_buff + 4, pst_param->auc_mac_ra);

    /* ����TA */
    oal_set_mac_addr(puc_buff + 10, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    return MAC_80211_CTL_HEADER_LEN;
}

/*****************************************************************************
 �� �� ��  : dmac_test_encap_init
 ��������  : ��ʼ����֡����ָ��
 �������  : pst_encap_fun: ָ���������ָ��
 �������  : ��
 �� �� ֵ  :��ȡ��֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_test_encap_init(dmac_test_encap_frame *pst_encap_fun)
{
    if(OAL_PTR_NULL == pst_encap_fun)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_encap_fun[MAC_TEST_MGMT_BCST] =     dmac_test_encap_mgmt_bcst;
    pst_encap_fun[MAC_TEST_MGMT_MCST] =     dmac_test_encap_mgmt_mcst;
    pst_encap_fun[MAC_TEST_ATIM_UCST] =     dmac_test_encap_mgmt_atim;
    pst_encap_fun[MAC_TEST_UCST]      =     dmac_test_encap_mgmt_ucst;
    pst_encap_fun[MAC_TEST_CTL_BCST]  =     dmac_test_encap_ctl_bcst;
    pst_encap_fun[MAC_TEST_CTL_MCST]  =     dmac_test_encap_ctl_mcst;
    pst_encap_fun[MAC_TEST_CTL_UCST]  =     dmac_test_encap_ctl_ucst;
    pst_encap_fun[MAC_TEST_ACK_UCST]  =     dmac_test_encap_ack_ucst;
    pst_encap_fun[MAC_TEST_CTS_UCST]  =     dmac_test_encap_cts_ucst;
    pst_encap_fun[MAC_TEST_RTS_UCST]  =     dmac_test_encap_rts_ucst;
    pst_encap_fun[MAC_TEST_BA_UCST]   =     dmac_test_encap_ba;
    pst_encap_fun[MAC_TEST_CF_END_UCST] =   dmac_test_encap_cf_end_ucst;
    pst_encap_fun[MAC_TEST_TA_RA_EUQAL] =   dmac_test_encap_mgmt_ucst_ra_equal_ta;
    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_test_get_encap_func
 ��������  : ��ȡ��֡����ָ��
 �������  : en_frame_type ֡����
 �������  : ��
 �� �� ֵ  :��ȡ��֡����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
dmac_test_encap_frame  dmac_test_get_encap_func(mac_test_frame_type_enum_uint8 en_frame_type)
{
    dmac_test_encap_frame *pst_encap;
    if(MAC_TEST_MAX_TYPE_NUM <= en_frame_type)
    {
        OAM_ERROR_LOG1(0, OAM_SF_FRAME_FILTER,
                          "{dmac_test_get_encap_func::en_frame_type=%u Err!}\r\n",
                            en_frame_type);
        return OAL_PTR_NULL;
    }

    pst_encap = dmac_test_get_encap_frame();
    if(OAL_PTR_NULL == pst_encap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRAME_FILTER, "{dmac_test_get_encap_func::pst_encap Err!}\r\n");
        return OAL_PTR_NULL;
    }
    return pst_encap[en_frame_type];
}



#endif /*_PRE_WLAN_CHIP_TEST*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

