/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_mgmt_bss_comm.c
  �� �� ��   : ����
  ��    ��   : huxiaotong
  ��������   : 2013��4��10��
  ����޸�   :
  ��������   : HMACģ���£�AP��STA���õĹ���֡�ӿ�ʵ�ֵ�Դ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��4��10��
    ��    ��   : huxiaotong
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
#include "wlan_spec.h"
#include "mac_vap.h"
#include "mac_ie.h"
#include "mac_frame.h"
#include "hmac_mgmt_bss_comm.h"
#include "mac_resource.h"
#include "hmac_device.h"
#include "hmac_resource.h"
#include "hmac_fsm.h"
#include "hmac_encap_frame.h"
#include "hmac_tx_amsdu.h"
#include "hmac_mgmt_ap.h"
#include "hmac_mgmt_sta.h"
#include "hmac_blockack.h"
#include "hmac_p2p.h"
#ifdef _PRE_WLAN_FEATURE_HILINK
#include "hmac_fbt_main.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_MGMT_BSS_COMM_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

oal_uint8 g_auc_avail_protocol_mode[WLAN_PROTOCOL_BUTT][WLAN_PROTOCOL_BUTT] =
{
    {WLAN_LEGACY_11A_MODE, WLAN_PROTOCOL_BUTT,   WLAN_PROTOCOL_BUTT,   WLAN_PROTOCOL_BUTT,     WLAN_PROTOCOL_BUTT,      WLAN_LEGACY_11A_MODE,   WLAN_LEGACY_11A_MODE, WLAN_PROTOCOL_BUTT, WLAN_PROTOCOL_BUTT, WLAN_PROTOCOL_BUTT},
    {WLAN_PROTOCOL_BUTT  , WLAN_LEGACY_11B_MODE, WLAN_LEGACY_11B_MODE, WLAN_LEGACY_11B_MODE,   WLAN_LEGACY_11B_MODE,    WLAN_LEGACY_11B_MODE,   WLAN_LEGACY_11B_MODE, WLAN_PROTOCOL_BUTT, WLAN_PROTOCOL_BUTT, WLAN_PROTOCOL_BUTT},
    {WLAN_PROTOCOL_BUTT  , WLAN_PROTOCOL_BUTT,   WLAN_LEGACY_11G_MODE, WLAN_LEGACY_11G_MODE,   WLAN_LEGACY_11G_MODE,    WLAN_LEGACY_11G_MODE,   WLAN_LEGACY_11G_MODE, WLAN_PROTOCOL_BUTT, WLAN_PROTOCOL_BUTT, WLAN_LEGACY_11G_MODE},
    {WLAN_PROTOCOL_BUTT  , WLAN_LEGACY_11B_MODE, WLAN_LEGACY_11G_MODE, WLAN_MIXED_ONE_11G_MODE,WLAN_MIXED_ONE_11G_MODE, WLAN_MIXED_ONE_11G_MODE,WLAN_MIXED_ONE_11G_MODE, WLAN_PROTOCOL_BUTT, WLAN_PROTOCOL_BUTT, WLAN_LEGACY_11G_MODE},
    {WLAN_PROTOCOL_BUTT  , WLAN_LEGACY_11B_MODE, WLAN_LEGACY_11G_MODE, WLAN_MIXED_ONE_11G_MODE,WLAN_MIXED_TWO_11G_MODE, WLAN_MIXED_ONE_11G_MODE,WLAN_MIXED_ONE_11G_MODE, WLAN_PROTOCOL_BUTT, WLAN_PROTOCOL_BUTT, WLAN_LEGACY_11G_MODE},
    {WLAN_LEGACY_11A_MODE, WLAN_LEGACY_11B_MODE, WLAN_LEGACY_11G_MODE, WLAN_MIXED_ONE_11G_MODE,WLAN_MIXED_ONE_11G_MODE, WLAN_HT_MODE,           WLAN_HT_MODE,         WLAN_HT_ONLY_MODE,  WLAN_PROTOCOL_BUTT, WLAN_HT_11G_MODE},
    {WLAN_LEGACY_11A_MODE, WLAN_LEGACY_11B_MODE, WLAN_LEGACY_11G_MODE, WLAN_MIXED_ONE_11G_MODE,WLAN_MIXED_ONE_11G_MODE, WLAN_HT_MODE,           WLAN_VHT_MODE,        WLAN_HT_ONLY_MODE,  WLAN_VHT_ONLY_MODE, WLAN_PROTOCOL_BUTT},
    {WLAN_PROTOCOL_BUTT,   WLAN_PROTOCOL_BUTT  , WLAN_PROTOCOL_BUTT  , WLAN_PROTOCOL_BUTT,     WLAN_PROTOCOL_BUTT,      WLAN_HT_ONLY_MODE,      WLAN_HT_ONLY_MODE,    WLAN_HT_ONLY_MODE,  WLAN_HT_ONLY_MODE,  WLAN_HT_ONLY_MODE},
    {WLAN_PROTOCOL_BUTT,   WLAN_PROTOCOL_BUTT  , WLAN_PROTOCOL_BUTT  , WLAN_PROTOCOL_BUTT,     WLAN_PROTOCOL_BUTT,      WLAN_PROTOCOL_BUTT,     WLAN_VHT_ONLY_MODE,   WLAN_PROTOCOL_BUTT, WLAN_VHT_ONLY_MODE, WLAN_PROTOCOL_BUTT},
    {WLAN_PROTOCOL_BUTT,   WLAN_PROTOCOL_BUTT  , WLAN_LEGACY_11G_MODE, WLAN_LEGACY_11G_MODE,   WLAN_LEGACY_11G_MODE,    WLAN_HT_11G_MODE,       WLAN_PROTOCOL_BUTT,   WLAN_HT_ONLY_MODE,  WLAN_PROTOCOL_BUTT, WLAN_HT_11G_MODE},
};

oal_uint32  hmac_mgmt_tx_addba_timeout(oal_void *p_arg);

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
/*****************************************************************************
 �� �� ��  : hmac_rx_ba_session_decr
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��24��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_rx_ba_session_decr(hmac_vap_stru *pst_hmac_vap, oal_uint8 uc_tidno)
{
    if (0 == pst_hmac_vap->uc_rx_ba_session_num)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_rx_ba_session_decr::tid[%d] rx_session already zero.}", uc_tidno);
        return;
    }

    pst_hmac_vap->uc_rx_ba_session_num--;

    OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_rx_ba_session_decr::tid[%d] rx_session[%d] remove.}", uc_tidno, pst_hmac_vap->uc_rx_ba_session_num);
}

/*****************************************************************************
 �� �� ��  : hmac_tx_ba_session_decr
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��24��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_tx_ba_session_decr(hmac_vap_stru *pst_hmac_vap, oal_uint8 uc_tidno)
{
    if (0 == pst_hmac_vap->uc_tx_ba_session_num)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_tx_ba_session_decr::tid[%d] tx_session already zero.}", uc_tidno);
        return;
    }

    pst_hmac_vap->uc_tx_ba_session_num--;

    OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_tx_ba_session_decr::tid[%d] tx_session[%d] remove.}", uc_tidno, pst_hmac_vap->uc_tx_ba_session_num);
}

/*****************************************************************************
 �� �� ��  : hmac_tx_ba_session_incr
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��24��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hmac_tx_ba_session_incr(hmac_vap_stru *pst_hmac_vap, oal_uint8 uc_tidno)
{
    pst_hmac_vap->uc_tx_ba_session_num++;

    OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_tx_ba_session_incr::tid[%d] tx_session[%d] setup.}", uc_tidno, pst_hmac_vap->uc_tx_ba_session_num);
}
#else
/*****************************************************************************
 �� �� ��  : hmac_rx_ba_session_decr
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��24��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_rx_ba_session_decr(mac_device_stru *pst_mac_device, oal_uint8 uc_tidno)
{
    if (0 == pst_mac_device->uc_rx_ba_session_num)
    {
        OAM_WARNING_LOG1(0, OAM_SF_BA, "{hmac_rx_ba_session_decr::tid[%d] rx_session already zero.}", uc_tidno);
        return;
    }

    pst_mac_device->uc_rx_ba_session_num--;

    OAM_WARNING_LOG2(0, OAM_SF_BA, "{hmac_rx_ba_session_decr::tid[%d] rx_session[%d] remove.}", uc_tidno, pst_mac_device->uc_rx_ba_session_num);
}

/*****************************************************************************
 �� �� ��  : hmac_tx_ba_session_decr
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��24��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_tx_ba_session_decr(mac_device_stru *pst_mac_device, oal_uint8 uc_tidno)
{
    if (0 == pst_mac_device->uc_tx_ba_session_num)
    {
        OAM_WARNING_LOG1(0, OAM_SF_BA, "{hmac_tx_ba_session_decr::tid[%d] tx_session already zero.}", uc_tidno);
        return;
    }

    pst_mac_device->uc_tx_ba_session_num--;

    OAM_WARNING_LOG2(0, OAM_SF_BA, "{hmac_tx_ba_session_decr::tid[%d] tx_session[%d] remove.}", uc_tidno, pst_mac_device->uc_tx_ba_session_num);
}

/*****************************************************************************
 �� �� ��  : hmac_tx_ba_session_incr
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��24��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hmac_tx_ba_session_incr(mac_device_stru *pst_mac_device, oal_uint8 uc_tidno)
{
    pst_mac_device->uc_tx_ba_session_num++;

    OAM_WARNING_LOG2(0, OAM_SF_BA, "{hmac_tx_ba_session_incr::tid[%d] tx_session[%d] setup.}", uc_tidno, pst_mac_device->uc_tx_ba_session_num);
}
#endif
/*****************************************************************************
 �� �� ��  : hmac_mgmt_encap_addba_req
 ��������  : ��װADDBA_REQ֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��9��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint16  hmac_mgmt_encap_addba_req(
                hmac_vap_stru          *pst_vap,
                oal_uint8              *puc_data,
                dmac_ba_tx_stru        *pst_tx_ba,
                oal_uint8               uc_tid)
{
    oal_uint16  us_index = 0;
    oal_uint16  us_ba_param;
    if ((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == puc_data) || (OAL_PTR_NULL == pst_tx_ba))
    {
        OAM_ERROR_LOG3(0, OAM_SF_BA, "{hmac_mgmt_encap_addba_req::null param.vap:%x data:%x ba:%x}",pst_vap,puc_data,pst_tx_ba);
        return OAL_ERR_CODE_PTR_NULL;
    }

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
    /*                Set the fields in the frame header                     */
    /*************************************************************************/

    /* Frame Control Field ��ֻ��Ҫ����Type/Subtypeֵ����������Ϊ0 */
    mac_hdr_set_frame_control(puc_data, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_ACTION);

    /* DA is address of STA requesting association */
    oal_set_mac_addr(puc_data + 4, pst_tx_ba->puc_dst_addr);

    /* SA��ֵΪdot11MACAddress��ֵ */
    oal_set_mac_addr(puc_data + 10, pst_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    oal_set_mac_addr(puc_data + 16, pst_vap->st_vap_base_info.auc_bssid);

    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /* ������ָ��frame body��ʼλ�� */
    us_index = MAC_80211_FRAME_LEN;

    /* ����Category */
    puc_data[us_index++] = MAC_ACTION_CATEGORY_BA;

    /* ����Action */
    puc_data[us_index++] = MAC_BA_ACTION_ADDBA_REQ;

    /* ����Dialog Token */
    puc_data[us_index++] = pst_tx_ba->uc_dialog_token;

    /*
        ����Block Ack Parameter set field
        bit0 - AMSDU Allowed
        bit1 - Immediate or Delayed block ack
        bit2-bit5 - TID
        bit6-bit15 -  Buffer size
    */
    us_ba_param = pst_tx_ba->en_amsdu_supp;         /* bit0 */
    us_ba_param |= (pst_tx_ba->uc_ba_policy << 1);  /* bit1 */
    us_ba_param |= (uc_tid << 2);                   /* bit2 */

    us_ba_param |= (oal_uint16)(pst_tx_ba->us_baw_size << 6);   /* bit6 */


    puc_data[us_index++] = (oal_uint8)(us_ba_param & 0xFF);
    puc_data[us_index++] = (oal_uint8)((us_ba_param >> 8) & 0xFF);

    /* ����BlockAck timeout */
    puc_data[us_index++] = (oal_uint8)(pst_tx_ba->us_ba_timeout & 0xFF);
    puc_data[us_index++] = (oal_uint8)((pst_tx_ba->us_ba_timeout >> 8) & 0xFF);

    /*
        Block ack starting sequence number�ֶ���Ӳ������
        bit0-bit3 fragmentnumber
        bit4-bit15: sequence number
    */

    /* us_buf_seq�˴��ݲ���д����dmac��Ჹ����д */
    *(oal_uint16 *)&puc_data[us_index++] = 0;
    us_index++;
    //puc_data[us_index++] = 0;
    //puc_data[us_index++] = 0;

    /* ���ص�֡�����в�����FCS */
    return us_index;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_encap_addba_rsp
 ��������  : ��װADDBA_RSP֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��9��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint16  hmac_mgmt_encap_addba_rsp(
                hmac_vap_stru      *pst_vap,
                oal_uint8          *puc_data,
                hmac_ba_rx_stru    *pst_addba_rsp,
                oal_uint8           uc_tid,
                oal_uint8           uc_status)
{
    oal_uint16  us_index    = 0;
    oal_uint16  us_ba_param  = 0;
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    hmac_user_stru *pst_hmac_user;
    hmac_user_btcoex_stru *pst_hmac_user_btcoex;
#endif
    if ((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == puc_data) || (OAL_PTR_NULL == pst_addba_rsp))
    {
        OAM_ERROR_LOG3(0, OAM_SF_BA, "{hmac_mgmt_encap_addba_req::null param.vap:%x data:%x rsp:%x}",pst_vap,puc_data,pst_addba_rsp);
        return OAL_ERR_CODE_PTR_NULL;
    }

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
    /*                Set the fields in the frame header                     */
    /*************************************************************************/

    /* All the fields of the Frame Control Field are set to zero. Only the   */
    /* Type/Subtype field is set.                                            */
    mac_hdr_set_frame_control(puc_data, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_ACTION);

    /* DA is address of STA requesting association */
    oal_set_mac_addr(puc_data + 4, pst_addba_rsp->puc_transmit_addr);

    /* SA is the dot11MACAddress */
    oal_set_mac_addr(puc_data + 10, pst_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    oal_set_mac_addr(puc_data + 16, pst_vap->st_vap_base_info.auc_bssid);

    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/
    /*************************************************************************/
    /*             ADDBA Response Frame - Frame Body                         */
    /*    ---------------------------------------------------------------    */
    /*    | Category | Action | Dialog | Status  | Parameters | Timeout |    */
    /*    ---------------------------------------------------------------    */
    /*    | 1        | 1      | 1      | 2       | 2          | 2       |    */
    /*    ---------------------------------------------------------------    */
    /*                                                                       */
    /*************************************************************************/

    /* Initialize index and the frame data pointer */
    us_index= MAC_80211_FRAME_LEN;

    /* Action Category���� */
    puc_data[us_index++] = MAC_ACTION_CATEGORY_BA;

    /* �ض�Action�����µ�action��֡���� */
    puc_data[us_index++] = MAC_BA_ACTION_ADDBA_RSP;

    /* Dialog Token�����ã���Ҫ��req��copy���� */
    puc_data[us_index++] = pst_addba_rsp->uc_dialog_token;

    /* ״̬������ */
    puc_data[us_index++] = uc_status;
    puc_data[us_index++]  = 0;

    /* Block Ack Parameter���� */
    /* B0 - AMSDU Support, B1- Immediate or Delayed block ack */
    /* B2-B5 : TID, B6-B15: Buffer size */
    us_ba_param  = pst_addba_rsp->en_amsdu_supp;                    /* BIT0 */
    us_ba_param |= (pst_addba_rsp->uc_ba_policy << 1);              /* BIT1 */
    us_ba_param |= (uc_tid << 2);                                   /* BIT2 */
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    /* �ֶ����þۺϸ���������ɾ��BAʱ������64�ۺ� */
    pst_hmac_user = mac_vap_get_hmac_user_by_addr(&(pst_vap->st_vap_base_info), pst_addba_rsp->puc_transmit_addr);

    if (OAL_PTR_NULL != pst_hmac_user)
    {
        if ((WLAN_VAP_MODE_BSS_STA == pst_vap->st_vap_base_info.en_vap_mode)
            && (WLAN_LEGACY_VAP_MODE == pst_vap->st_vap_base_info.en_p2p_mode))
        {
            pst_hmac_user_btcoex = &(pst_hmac_user->st_hmac_user_btcoex);
            if (OAL_FALSE == pst_hmac_user_btcoex->st_hmac_btcoex_addba_req.uc_delba_enable)
            {
                us_ba_param |= (oal_uint16)(0x0008 << 6);
            }
            else if(pst_hmac_user_btcoex->us_ba_size)
            {
                us_ba_param |= (oal_uint16)(pst_hmac_user_btcoex->us_ba_size << 6);   /* BIT6 */
            }
            else
            {
                us_ba_param |= (oal_uint16)(pst_addba_rsp->us_baw_size << 6);   /* BIT6 */
            }
        }
        else
        {
            us_ba_param |= (oal_uint16)(pst_addba_rsp->us_baw_size << 6);   /* BIT6 */
        }
    }
    else
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{hmac_mgmt_encap_addba_rsp::user ptr null.}");
        us_ba_param |= (oal_uint16)(pst_addba_rsp->us_baw_size << 6);   /* BIT6 */
    }
#else
    us_ba_param |= (oal_uint16)(pst_addba_rsp->us_baw_size << 6);   /* BIT6 */
#endif

    puc_data[us_index++] = (oal_uint8)(us_ba_param & 0xFF);
    puc_data[us_index++] = (oal_uint8)((us_ba_param >> 8) & 0xFF);

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    /* DTS2015111909158 aput������ɾ��ba�Ự��������Ϊ���նˣ�ͬ��sta�ڻỰ��ʱɾ��ba�Ự��*/
    puc_data[us_index++] = (oal_uint8)(pst_addba_rsp->us_ba_timeout & 0xFF);
    puc_data[us_index++] = (oal_uint8)((pst_addba_rsp->us_ba_timeout >> 8) & 0xFF);
#else
    /* BlockAck timeoutֵ����DTS2015111901526 ���timeout���������� */
    puc_data[us_index++] = 0x00;
    puc_data[us_index++] = 0x00;
#endif

    /* ���ص�֡�����в�����FCS */
    return us_index;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_encap_delba
 ��������  : ��װDELBA֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��9��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint16  hmac_mgmt_encap_delba(
                hmac_vap_stru                      *pst_vap,
                oal_uint8                          *puc_data,
                oal_uint8                          *puc_addr,
                oal_uint8                           uc_tid,
                mac_delba_initiator_enum_uint8      en_initiator,
                oal_uint8                           reason)
{
    oal_uint16  us_index = 0;

    if ((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == puc_data) || (OAL_PTR_NULL == puc_addr))
    {
        OAM_ERROR_LOG3(0, OAM_SF_BA, "{hmac_mgmt_encap_delba::null param, %d %d %d.}", pst_vap, puc_data, puc_addr);
        return OAL_ERR_CODE_PTR_NULL;
    }

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
    /*                Set the fields in the frame header                     */
    /*************************************************************************/

    /* All the fields of the Frame Control Field are set to zero. Only the   */
    /* Type/Subtype field is set.                                            */
    mac_hdr_set_frame_control(puc_data, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_ACTION);

    /* duration */
    puc_data[2] = 0;
    puc_data[3] = 0;

    /* DA is address of STA requesting association */
    oal_set_mac_addr(puc_data + 4, puc_addr);

    /* SA is the dot11MACAddress */
    oal_set_mac_addr(puc_data + 10, pst_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    oal_set_mac_addr(puc_data + 16, pst_vap->st_vap_base_info.auc_bssid);

    /* seq control */
    puc_data[22] = 0;
    puc_data[23] = 0;

    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*             DELBA Response Frame - Frame Body                         */
    /*        -------------------------------------------------              */
    /*        | Category | Action |  Parameters | Reason code |              */
    /*        -------------------------------------------------              */
    /*        | 1        | 1      |       2     | 2           |              */
    /*        -------------------------------------------------              */
    /*                          Parameters                                   */
    /*                  -------------------------------                      */
    /*                  | Reserved | Initiator |  TID  |                     */
    /*                  -------------------------------                      */
    /*             bit  |    11    |    1      |  4    |                     */
    /*                  --------------------------------                     */
    /*************************************************************************/
    /* Initialize index and the frame data pointer */
    us_index = MAC_80211_FRAME_LEN;

    /* Category */
    puc_data[us_index++] = MAC_ACTION_CATEGORY_BA;

    /* Action */
    puc_data[us_index++] = MAC_BA_ACTION_DELBA;

    /* DELBA parameter set */
    /* B0 - B10 -reserved */
    /* B11 - initiator */
    /* B12-B15 - TID */
    puc_data[us_index++]  = 0;
    puc_data[us_index]    = (oal_uint8)(en_initiator << 3);
    puc_data[us_index++] |= (oal_uint8)(uc_tid << 4);

    /* Reason field */
    /* Reason can be either of END_BA, QSTA_LEAVING, UNKNOWN_BA */
    puc_data[us_index++] = reason;
    puc_data[us_index++] = 0;

    /* ���ص�֡�����в�����FCS */
    return us_index;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_tx_addba_req
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��14��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_mgmt_tx_addba_req(
                hmac_vap_stru              *pst_hmac_vap,
                hmac_user_stru             *pst_hmac_user,
                mac_action_mgmt_args_stru  *pst_action_args)
{
    mac_device_stru            *pst_device;
    mac_vap_stru               *pst_mac_vap;
    frw_event_mem_stru         *pst_event_mem;      /* �����¼����ص��ڴ�ָ�� */
    oal_netbuf_stru            *pst_addba_req;
    dmac_ba_tx_stru             st_tx_ba;
    oal_uint8                   uc_tidno;
    oal_uint16                  us_frame_len;
    frw_event_stru             *pst_hmac_to_dmac_ctx_event;
    dmac_tx_event_stru         *pst_tx_event;
    dmac_ctx_action_event_stru  st_wlan_ctx_action;
    oal_uint32                  ul_ret;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_tx_ctl_stru            *pst_tx_ctl;
#endif

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_hmac_user) || (OAL_PTR_NULL == pst_action_args))
    {
        OAM_ERROR_LOG3(0, OAM_SF_BA, "{hmac_mgmt_tx_addba_req::null param, %d %d %d.}", pst_hmac_vap, pst_hmac_user, pst_action_args);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);
    /* DTS2015120203304: ȷ��vap���ڹ���״̬ */
    if (MAC_VAP_STATE_BUTT == pst_mac_vap->en_vap_state)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_addba_req:: vap has been down/del, vap_state[%d].}",pst_mac_vap->en_vap_state);
        return OAL_FAIL;
    }

    /* ��ȡdevice�ṹ */
    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_addba_req::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����ADDBA_REQ����֡�ڴ� */
    pst_addba_req = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if (OAL_PTR_NULL == pst_addba_req)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_addba_req::pst_addba_req null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEM_NETBUF_TRACE(pst_addba_req, OAL_TRUE);

    OAL_MEMZERO(oal_netbuf_cb(pst_addba_req), OAL_NETBUF_CB_SIZE());
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_addba_req);
#endif

    OAL_NETBUF_PREV(pst_addba_req) = OAL_PTR_NULL;
    OAL_NETBUF_NEXT(pst_addba_req) = OAL_PTR_NULL;

    uc_tidno = (oal_uint8)(pst_action_args->ul_arg1);
    pst_hmac_vap->uc_ba_dialog_token++;
    st_tx_ba.uc_dialog_token = pst_hmac_vap->uc_ba_dialog_token;  /* ��֤ba�Ự�����ܹ����� */
    st_tx_ba.us_baw_size     = (oal_uint8)(pst_action_args->ul_arg2);
    st_tx_ba.uc_ba_policy    = (oal_uint8)(pst_action_args->ul_arg3);
    st_tx_ba.us_ba_timeout   = (oal_uint16)(pst_action_args->ul_arg4);
    st_tx_ba.puc_dst_addr    = pst_hmac_user->st_user_base_info.auc_user_mac_addr;

    /* ���˶�AMPDU+AMSDU��֧�� */
    st_tx_ba.en_amsdu_supp   = (oal_bool_enum_uint8)pst_hmac_vap->en_amsdu_ampdu_active;

    /*lint -e502*/
    if (OAL_FALSE == st_tx_ba.en_amsdu_supp)
    {
        HMAC_USER_SET_AMSDU_NOT_SUPPORT(pst_hmac_user, uc_tidno);
    }
    /*lint +e502*/
    else
    {
        HMAC_USER_SET_AMSDU_SUPPORT(pst_hmac_user, uc_tidno);
    }

    /* ���÷�װ����֡�ӿ� */
    us_frame_len = hmac_mgmt_encap_addba_req(pst_hmac_vap, oal_netbuf_data(pst_addba_req), &st_tx_ba, uc_tidno);
    OAL_MEMZERO((oal_uint8*)&st_wlan_ctx_action, OAL_SIZEOF(st_wlan_ctx_action));
    /*��ֵҪ����Dmac����Ϣ*/
    st_wlan_ctx_action.us_frame_len        = us_frame_len;
    st_wlan_ctx_action.uc_hdr_len          = MAC_80211_FRAME_LEN;
    st_wlan_ctx_action.en_action_category  = MAC_ACTION_CATEGORY_BA;
    st_wlan_ctx_action.uc_action           = MAC_BA_ACTION_ADDBA_REQ;
    st_wlan_ctx_action.us_user_idx         = pst_hmac_user->st_user_base_info.us_assoc_id;
    st_wlan_ctx_action.uc_tidno            = uc_tidno;
    st_wlan_ctx_action.uc_dialog_token     = st_tx_ba.uc_dialog_token;
    st_wlan_ctx_action.uc_ba_policy        = st_tx_ba.uc_ba_policy;
    st_wlan_ctx_action.us_baw_size         = st_tx_ba.us_baw_size;
    st_wlan_ctx_action.us_ba_timeout       = st_tx_ba.us_ba_timeout;

    oal_memcopy((oal_uint8 *)(oal_netbuf_data(pst_addba_req) + us_frame_len), (oal_uint8 *)&st_wlan_ctx_action, OAL_SIZEOF(dmac_ctx_action_event_stru));
    oal_netbuf_put(pst_addba_req, (us_frame_len + OAL_SIZEOF(dmac_ctx_action_event_stru)));

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_tx_ctl->us_mpdu_len = us_frame_len + OAL_SIZEOF(dmac_ctx_action_event_stru);
#endif

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_addba_req::pst_event_mem null.}");
        oal_netbuf_free(pst_addba_req);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_to_dmac_ctx_event = (frw_event_stru *)pst_event_mem->puc_data;
    FRW_EVENT_HDR_INIT(&(pst_hmac_to_dmac_ctx_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_ACTION,
                       OAL_SIZEOF(dmac_tx_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    pst_tx_event = (dmac_tx_event_stru *)(pst_hmac_to_dmac_ctx_event->auc_event_data);
    pst_tx_event->pst_netbuf    = pst_addba_req;
    pst_tx_event->us_frame_len  = us_frame_len + OAL_SIZEOF(dmac_ctx_action_event_stru);

    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (ul_ret != OAL_SUCC)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_addba_req::frw_event_dispatch_event failed[%d].}", ul_ret);
        oal_netbuf_free(pst_addba_req);
        FRW_EVENT_FREE(pst_event_mem);
        return ul_ret;
    }

    FRW_EVENT_FREE(pst_event_mem);

    /* ���¶�Ӧ��TID��Ϣ */
    pst_hmac_user->ast_tid_info[uc_tidno].st_ba_tx_info.en_ba_status    = DMAC_BA_INPROGRESS;
    pst_hmac_user->ast_tid_info[uc_tidno].st_ba_tx_info.uc_dialog_token = st_tx_ba.uc_dialog_token;

#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
    hmac_tx_ba_session_incr(pst_hmac_vap, uc_tidno);
#else
    hmac_tx_ba_session_incr(pst_device, uc_tidno);
#endif
    /* ����ADDBA��ʱ��ʱ�� */
    FRW_TIMER_CREATE_TIMER(&pst_hmac_user->ast_tid_info[uc_tidno].st_ba_tx_info.st_addba_timer,
                           hmac_mgmt_tx_addba_timeout,
                           WLAN_ADDBA_TIMEOUT,
                           &pst_hmac_user->ast_tid_info[uc_tidno].st_ba_tx_info.st_alarm_data,
                           OAL_FALSE,
                           OAM_MODULE_ID_HMAC,
                           pst_device->ul_core_id);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_tx_addba_rsp
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��29��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_mgmt_tx_addba_rsp(
                hmac_vap_stru              *pst_hmac_vap,
                hmac_user_stru             *pst_hmac_user,
                hmac_ba_rx_stru            *pst_ba_rx_info,
                oal_uint8                   uc_tid,
                oal_uint8                   uc_status)
{
    mac_device_stru                *pst_device;
    mac_vap_stru                   *pst_mac_vap;
    frw_event_mem_stru             *pst_event_mem;      /* �����¼����ص��ڴ�ָ�� */
    frw_event_stru                 *pst_hmac_to_dmac_ctx_event;
    dmac_tx_event_stru             *pst_tx_event;
    dmac_ctx_action_event_stru      st_wlan_ctx_action;
    oal_netbuf_stru                *pst_addba_rsp;
    oal_uint16                      us_frame_len;
    oal_uint32                      ul_ret = OAL_SUCC;
    mac_tx_ctl_stru                *pst_tx_ctl;

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_hmac_user) || (OAL_PTR_NULL == pst_ba_rx_info))
    {
        OAM_ERROR_LOG3(0, OAM_SF_BA, "{hmac_mgmt_tx_addba_rsp::send addba rsp failed, null param, %d %d %d.}", pst_hmac_vap, pst_hmac_user, pst_ba_rx_info);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);
    /* DTS2015120203304: ȷ��vap���ڹ���״̬ */
    if (MAC_VAP_STATE_BUTT == pst_mac_vap->en_vap_state)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_addba_rsp:: vap has been down/del, vap_state[%d].}",pst_mac_vap->en_vap_state);
        return OAL_FAIL;
    }

    /* ��ȡdevice�ṹ */
    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_addba_rsp::send addba rsp failed, pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����ADDBA_RSP����֡�ڴ� */
    pst_addba_rsp = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if (OAL_PTR_NULL == pst_addba_rsp)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_addba_rsp::send addba rsp failed, pst_addba_rsp mem alloc failed.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEM_NETBUF_TRACE(pst_addba_rsp, OAL_TRUE);
    OAL_MEMZERO(oal_netbuf_cb(pst_addba_rsp), OAL_NETBUF_CB_SIZE());

    OAL_NETBUF_PREV(pst_addba_rsp) = OAL_PTR_NULL;
    OAL_NETBUF_NEXT(pst_addba_rsp) = OAL_PTR_NULL;

    /* ��дnetbuf��cb�ֶΣ������͹���֡�ͷ�����ɽӿ�ʹ�� */
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_addba_rsp);
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl)   = (oal_uint8)pst_hmac_user->st_user_base_info.us_assoc_id;
    mac_set_cb_tid(pst_tx_ctl, uc_tid);
    mac_set_cb_is_amsdu(pst_tx_ctl, OAL_FALSE);

    us_frame_len = hmac_mgmt_encap_addba_rsp(pst_hmac_vap, oal_netbuf_data(pst_addba_rsp), pst_ba_rx_info, uc_tid, uc_status);
    OAL_MEMZERO((oal_uint8*)&st_wlan_ctx_action, OAL_SIZEOF(st_wlan_ctx_action));
    st_wlan_ctx_action.en_action_category  = MAC_ACTION_CATEGORY_BA;
    st_wlan_ctx_action.uc_action           = MAC_BA_ACTION_ADDBA_RSP;
    st_wlan_ctx_action.uc_hdr_len          = MAC_80211_FRAME_LEN;
    st_wlan_ctx_action.us_baw_size         = pst_ba_rx_info->us_baw_size;
    st_wlan_ctx_action.us_frame_len        = us_frame_len;
    st_wlan_ctx_action.us_user_idx         = pst_hmac_user->st_user_base_info.us_assoc_id;
    st_wlan_ctx_action.uc_tidno            = uc_tid;
    st_wlan_ctx_action.uc_status           = uc_status;
    st_wlan_ctx_action.us_ba_timeout       = pst_ba_rx_info->us_ba_timeout;
    st_wlan_ctx_action.en_back_var         = pst_ba_rx_info->en_back_var;
    st_wlan_ctx_action.uc_lut_index        = pst_ba_rx_info->uc_lut_index;
    st_wlan_ctx_action.us_baw_start        = pst_ba_rx_info->us_baw_start;
    st_wlan_ctx_action.uc_ba_policy        = pst_ba_rx_info->uc_ba_policy;

    oal_memcopy((oal_uint8 *)(oal_netbuf_data(pst_addba_rsp) + us_frame_len), (oal_uint8 *)&st_wlan_ctx_action, OAL_SIZEOF(dmac_ctx_action_event_stru));
    oal_netbuf_put(pst_addba_rsp, (us_frame_len + OAL_SIZEOF(dmac_ctx_action_event_stru)));

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_tx_ctl->us_mpdu_len = us_frame_len + OAL_SIZEOF(dmac_ctx_action_event_stru);
#endif

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_addba_rsp::send addba rsp failed, pst_event_mem mem alloc failed.}");
        oal_netbuf_free(pst_addba_rsp);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_to_dmac_ctx_event = (frw_event_stru *)pst_event_mem->puc_data;
    FRW_EVENT_HDR_INIT(&(pst_hmac_to_dmac_ctx_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_ACTION,
                       OAL_SIZEOF(dmac_tx_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    /*��д�¼�payload */
    pst_tx_event = (dmac_tx_event_stru *)(pst_hmac_to_dmac_ctx_event->auc_event_data);
    pst_tx_event->pst_netbuf    = pst_addba_rsp;
    pst_tx_event->us_frame_len  = us_frame_len + OAL_SIZEOF(dmac_ctx_action_event_stru);


    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (ul_ret != OAL_SUCC)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_addba_rsp::send addba rsp failed, frw_event_dispatch_event failed[%d].}", ul_ret);
        oal_netbuf_free(pst_addba_rsp);
    }
    else
    {
        pst_ba_rx_info->en_ba_status = DMAC_BA_COMPLETE;
    }

    FRW_EVENT_FREE(pst_event_mem);
    return ul_ret;
}
/*****************************************************************************
 �� �� ��  : hmac_mgmt_tx_delba
 ��������  : ����DELBA����ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��14��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_mgmt_tx_delba(
                hmac_vap_stru              *pst_hmac_vap,
                hmac_user_stru             *pst_hmac_user,
                mac_action_mgmt_args_stru  *pst_action_args)
{
    mac_device_stru                  *pst_device;
    mac_vap_stru                     *pst_mac_vap;
    frw_event_mem_stru               *pst_event_mem;      /* �����¼����ص��ڴ�ָ�� */
    oal_netbuf_stru                  *pst_delba;
    oal_uint16                        us_frame_len;
    frw_event_stru                   *pst_hmac_to_dmac_ctx_event;
    dmac_tx_event_stru               *pst_tx_event;
    dmac_ctx_action_event_stru        st_wlan_ctx_action;
    mac_delba_initiator_enum_uint8    en_initiator;
    oal_uint32                        ul_ret;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_tx_ctl_stru                  *pst_tx_ctl;
#endif

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_hmac_user) || (OAL_PTR_NULL == pst_action_args))
    {
        OAM_ERROR_LOG3(0, OAM_SF_BA, "{hmac_mgmt_tx_delba::null param, %d %d %d.}", pst_hmac_vap, pst_hmac_user, pst_action_args);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);
    /* DTS2015120203304: ��ȷ��vap���ڹ���״̬ */
    if (MAC_VAP_STATE_BUTT == pst_mac_vap->en_vap_state)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_delba:: vap has been down/del, vap_state[%d].}",pst_mac_vap->en_vap_state);
        return OAL_FAIL;
    }

    /* ��ȡdevice�ṹ */
    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_delba::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if(DMAC_BA_INIT == pst_hmac_user->ast_tid_info[pst_action_args->ul_arg1].st_ba_tx_info.en_ba_status)
    {
        return OAL_SUCC;
    }

    /* ����DEL_BA����֡�ڴ� */
    pst_delba = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if (OAL_PTR_NULL == pst_delba)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_delba::pst_delba null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEM_NETBUF_TRACE(pst_delba, OAL_TRUE);

    OAL_MEMZERO(oal_netbuf_cb(pst_delba), OAL_NETBUF_CB_SIZE());
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_delba);
#endif

    OAL_NETBUF_PREV(pst_delba) = OAL_PTR_NULL;
    OAL_NETBUF_NEXT(pst_delba) = OAL_PTR_NULL;

    en_initiator = (oal_uint8)pst_action_args->ul_arg2;

    /* ���÷�װ����֡�ӿ� */
    us_frame_len = hmac_mgmt_encap_delba(pst_hmac_vap, (oal_uint8 *)OAL_NETBUF_HEADER(pst_delba), pst_action_args->puc_arg5, (oal_uint8)pst_action_args->ul_arg1, en_initiator, (oal_uint8)pst_action_args->ul_arg3);
    OAL_MEMZERO((oal_uint8*)&st_wlan_ctx_action, OAL_SIZEOF(st_wlan_ctx_action));
    st_wlan_ctx_action.us_frame_len        = us_frame_len;
    st_wlan_ctx_action.uc_hdr_len          = MAC_80211_FRAME_LEN;
    st_wlan_ctx_action.en_action_category  = MAC_ACTION_CATEGORY_BA;
    st_wlan_ctx_action.uc_action           = MAC_BA_ACTION_DELBA;
    st_wlan_ctx_action.us_user_idx         = pst_hmac_user->st_user_base_info.us_assoc_id;
    st_wlan_ctx_action.uc_tidno            = (oal_uint8)pst_action_args->ul_arg1;
    st_wlan_ctx_action.uc_initiator        = (oal_uint8)pst_action_args->ul_arg2;

    oal_memcopy((oal_uint8 *)(oal_netbuf_data(pst_delba) + us_frame_len), (oal_uint8 *)&st_wlan_ctx_action, OAL_SIZEOF(dmac_ctx_action_event_stru));
    oal_netbuf_put(pst_delba, (us_frame_len + OAL_SIZEOF(dmac_ctx_action_event_stru)));

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_tx_ctl->us_mpdu_len = us_frame_len + OAL_SIZEOF(dmac_ctx_action_event_stru);
#endif

    /* ���¼�����DMACģ�鷢�� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_delba::pst_event_mem null.}");
        /* �ͷŹ���֡�ڴ浽netbuf�ڴ�� */
        oal_netbuf_free(pst_delba);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����¼�ָ�� */
    pst_hmac_to_dmac_ctx_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_hmac_to_dmac_ctx_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_ACTION,
                       OAL_SIZEOF(dmac_tx_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    /*��д�¼�payload */
    pst_tx_event = (dmac_tx_event_stru *)(pst_hmac_to_dmac_ctx_event->auc_event_data);
    pst_tx_event->pst_netbuf    = pst_delba;
    pst_tx_event->us_frame_len  = us_frame_len + OAL_SIZEOF(dmac_ctx_action_event_stru);

    /* �ַ� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (ul_ret != OAL_SUCC)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_delba::frw_event_dispatch_event failed[%d].}", ul_ret);
        oal_netbuf_free(pst_delba);
        FRW_EVENT_FREE(pst_event_mem);

        return ul_ret;
    }

    FRW_EVENT_FREE(pst_event_mem);

    if (MAC_RECIPIENT_DELBA == en_initiator)
    {
        /* ���¶�Ӧ��TID��Ϣ */
        hmac_ba_reset_rx_handle(pst_device, &pst_hmac_user->ast_tid_info[pst_action_args->ul_arg1].pst_ba_rx_info, (oal_uint8)pst_action_args->ul_arg1, OAL_FALSE);
    }
    else
    {
        /* ���¶�Ӧ��TID��Ϣ */
        pst_hmac_user->ast_tid_info[pst_action_args->ul_arg1].st_ba_tx_info.en_ba_status = DMAC_BA_INIT;
        pst_hmac_user->auc_ba_flag[pst_action_args->ul_arg1] = 0;

#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
        hmac_tx_ba_session_decr(pst_hmac_vap, pst_hmac_user->ast_tid_info[pst_action_args->ul_arg1].uc_tid_no);
#else
        hmac_tx_ba_session_decr(pst_device, pst_hmac_user->ast_tid_info[pst_action_args->ul_arg1].uc_tid_no);
#endif
        /* ��ԭ����AMPDU��AMSDU��֧����� */
        HMAC_USER_SET_AMSDU_SUPPORT(pst_hmac_user, pst_action_args->ul_arg1);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_rx_addba_req
 ��������  : �ӿտڽ���ADDBA_REQ֡�Ĵ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��14��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��3��
    ��    ��   : houyin
    �޸�����   : ��Reorder���������Ϣ��ֲHmac

*****************************************************************************/
oal_uint32  hmac_mgmt_rx_addba_req(
                hmac_vap_stru              *pst_hmac_vap,
                hmac_user_stru             *pst_hmac_user,
                oal_uint8                  *puc_payload)
{
    mac_device_stru                *pst_device;
    mac_vap_stru                   *pst_mac_vap;
    oal_uint8                       uc_tid = 0;
    oal_uint8                       uc_status = MAC_SUCCESSFUL_STATUSCODE;
    oal_uint8                       uc_reorder_index;
    hmac_ba_rx_stru                *pst_ba_rx_stru;
    oal_uint32                      ul_ret;

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_hmac_user) || (OAL_PTR_NULL == puc_payload))
    {
        OAM_ERROR_LOG3(0, OAM_SF_BA, "{hmac_mgmt_rx_addba_req::addba req receive failed, null param, 0x%x 0x%x 0x%x.}", pst_hmac_vap, pst_hmac_user, puc_payload);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);

    /* 11n���������ſɽ���ampdu */
    if ((!(pst_mac_vap->en_protocol >= WLAN_HT_MODE)) || (!(pst_hmac_user->st_user_base_info.en_protocol_mode >= WLAN_HT_MODE)))
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_BA,
                      "{hmac_mgmt_rx_addba_req::ampdu is not supprot or not open, vap protocol mode = %d, user protocol mode = %d.}",
                       pst_mac_vap->en_protocol, pst_hmac_user->st_user_base_info.en_protocol_mode);
        return OAL_SUCC;
    }

    /* ��ȡdevice�ṹ */
    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_rx_addba_req::addba req receive failed, pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /******************************************************************/
    /*       ADDBA Request Frame - Frame Body                         */
    /* ---------------------------------------------------------------*/
    /* | Category | Action | Dialog | Parameters | Timeout | SSN     |*/
    /* ---------------------------------------------------------------*/
    /* | 1        | 1      | 1      | 2          | 2       | 2       |*/
    /* ---------------------------------------------------------------*/
    /*                                                                */
    /******************************************************************/

    uc_tid        = (puc_payload[3] & 0x3C) >> 2;
    if (uc_tid >= WLAN_TID_MAX_NUM)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_rx_addba_req::addba req receive failed, tid %d overflow.}", uc_tid);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    if (OAL_PTR_NULL != pst_hmac_user->ast_tid_info[uc_tid].pst_ba_rx_info)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_rx_addba_req::addba req received, but tid [%d] already set up.}", uc_tid);
        /* DTS2015042207613 addba rsp����ʧ��,�ٴ��ܵ�addba req���½���BA */
        hmac_ba_reset_rx_handle(pst_device, &pst_hmac_user->ast_tid_info[uc_tid].pst_ba_rx_info, uc_tid, OAL_FALSE);
        //return OAL_SUCC;
    }

    pst_hmac_user->ast_tid_info[uc_tid].pst_ba_rx_info = (hmac_ba_rx_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, (oal_uint16)OAL_SIZEOF(hmac_ba_rx_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_hmac_user->ast_tid_info[uc_tid].pst_ba_rx_info)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_rx_addba_req::addba req receive failed, pst_ba_rx_hdl mem alloc failed.tid[%d]}", uc_tid);

        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_ba_rx_stru = pst_hmac_user->ast_tid_info[uc_tid].pst_ba_rx_info;
    pst_ba_rx_stru->en_ba_status = DMAC_BA_INIT;
    pst_ba_rx_stru->uc_dialog_token = puc_payload[2];

    /*��ʼ��reorder����*/
    for (uc_reorder_index = 0; uc_reorder_index < WLAN_AMPDU_RX_BUFFER_SIZE; uc_reorder_index++)
    {
        pst_ba_rx_stru->ast_re_order_list[uc_reorder_index].in_use     = 0;
        pst_ba_rx_stru->ast_re_order_list[uc_reorder_index].us_seq_num = 0;
        pst_ba_rx_stru->ast_re_order_list[uc_reorder_index].uc_num_buf = 0;
        oal_netbuf_list_head_init(&(pst_ba_rx_stru->ast_re_order_list[uc_reorder_index].st_netbuf_head));
    }

    /*��ʼ�����մ���*/
    pst_ba_rx_stru->us_baw_start = (puc_payload[7] >> 4) | (puc_payload[8] << 4);
    pst_ba_rx_stru->us_baw_size  = (puc_payload[3] & 0xC0) >> 6;
    pst_ba_rx_stru->us_baw_size |= (puc_payload[4] << 2);
    if ((0 == pst_ba_rx_stru->us_baw_size) || (pst_ba_rx_stru->us_baw_size > WLAN_AMPDU_RX_BUFFER_SIZE))
    {
        pst_ba_rx_stru->us_baw_size = WLAN_AMPDU_RX_BUFFER_SIZE;
    }

    /* DTS2016010902690 ���goldenap�¹̼��汾���������� */
    if (1 == pst_ba_rx_stru->us_baw_size)
    {
        pst_ba_rx_stru->us_baw_size = WLAN_AMPDU_RX_BUFFER_SIZE;
    }

    pst_ba_rx_stru->us_baw_end   = DMAC_BA_SEQ_ADD(pst_ba_rx_stru->us_baw_start, (pst_ba_rx_stru->us_baw_size - 1));
    pst_ba_rx_stru->us_baw_tail  = DMAC_BA_SEQNO_SUB(pst_ba_rx_stru->us_baw_start, 1);
    pst_ba_rx_stru->us_baw_head  = DMAC_BA_SEQNO_SUB(pst_ba_rx_stru->us_baw_start, HMAC_BA_BMP_SIZE);
    pst_ba_rx_stru->uc_mpdu_cnt  = 0;
    pst_ba_rx_stru->en_is_ba     = OAL_TRUE;  //Ba session is processing

    /*��ʼ����ʱ����Դ*/
    pst_ba_rx_stru->st_alarm_data.pst_ba           = pst_ba_rx_stru;
    pst_ba_rx_stru->st_alarm_data.us_mac_user_idx  = pst_hmac_user->st_user_base_info.us_assoc_id;
    pst_ba_rx_stru->st_alarm_data.uc_vap_id        = pst_mac_vap->uc_vap_id;
    pst_ba_rx_stru->st_alarm_data.uc_tid           = uc_tid;
    pst_ba_rx_stru->st_alarm_data.us_timeout_times = 0;
    pst_ba_rx_stru->st_alarm_data.en_direction     = MAC_RECIPIENT_DELBA;
    pst_ba_rx_stru->en_timer_triggered             = OAL_FALSE;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_spin_lock_init(&pst_ba_rx_stru->st_ba_lock);
#endif

    /*Ba�Ự������ʼ��*/
    pst_ba_rx_stru->us_ba_timeout = puc_payload[5] | (puc_payload[6] << 8);
    pst_ba_rx_stru->en_amsdu_supp = 0;
    pst_ba_rx_stru->en_back_var   = MAC_BACK_COMPRESSED;
    pst_ba_rx_stru->puc_transmit_addr = pst_hmac_user->st_user_base_info.auc_user_mac_addr;
    pst_ba_rx_stru->uc_ba_policy      = (puc_payload[3] & 0x02) >> 1;

#ifndef _PRE_PROFILING_MODE
    /*profiling�����У����ն˲�ɾ��ba*/
    FRW_TIMER_CREATE_TIMER(&(pst_hmac_user->ast_tid_info[uc_tid].st_ba_timer),
                           hmac_ba_timeout_fn,
                           pst_hmac_vap->us_rx_timeout[WLAN_WME_TID_TO_AC(uc_tid)],
                           &(pst_ba_rx_stru->st_alarm_data),
                           OAL_FALSE,
                           OAM_MODULE_ID_HMAC,
                           pst_device->ul_core_id);
#endif
#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
    pst_hmac_vap->uc_rx_ba_session_num++;
#else
    pst_device->uc_rx_ba_session_num++;
#endif

    /* �жϽ����ܷ�ɹ� */
    uc_status = hmac_mgmt_check_set_rx_ba_ok(pst_hmac_vap, pst_ba_rx_stru, pst_device);
    if (MAC_SUCCESSFUL_STATUSCODE == uc_status)
    {
        pst_hmac_user->ast_tid_info[uc_tid].pst_ba_rx_info->en_ba_status = DMAC_BA_INPROGRESS;
    }

    ul_ret = hmac_mgmt_tx_addba_rsp(pst_hmac_vap, pst_hmac_user, pst_ba_rx_stru, uc_tid, uc_status);

    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_rx_addba_req::process addba req receive and send addba rsp, uc_tid[%d], uc_status[%d], baw_start[%d], baw_size[%d]}\r\n",
      uc_tid, uc_status, pst_ba_rx_stru->us_baw_start, pst_ba_rx_stru->us_baw_size);

    if ((MAC_SUCCESSFUL_STATUSCODE != uc_status) || (OAL_SUCC != ul_ret))
    {
        /*pst_hmac_user->ast_tid_info[uc_tid].pst_ba_rx_info�޸�Ϊ�ں������ÿգ�������
                ����һ��*/
        hmac_ba_reset_rx_handle(pst_device, &pst_hmac_user->ast_tid_info[uc_tid].pst_ba_rx_info, uc_tid, OAL_FALSE);
        pst_ba_rx_stru = OAL_PTR_NULL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_rx_addba_rsp
 ��������  : �ӿտڽ���ADDBA_RSP֡�Ĵ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��14��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_mgmt_rx_addba_rsp(
                hmac_vap_stru              *pst_hmac_vap,
                hmac_user_stru             *pst_hmac_user,
                oal_uint8                  *puc_payload)
{
    mac_device_stru            *pst_mac_device;
    mac_vap_stru               *pst_mac_vap;
    frw_event_mem_stru         *pst_event_mem;      /* �����¼����ص��ڴ�ָ�� */
    frw_event_stru             *pst_hmac_to_dmac_crx_sync;
    dmac_ctx_action_event_stru *pst_rx_addba_rsp_event;
    oal_uint8                   uc_tidno;
    hmac_tid_stru              *pst_tid;
    mac_action_mgmt_args_stru   st_action_args;
    oal_uint8                   uc_dialog_token;
    oal_uint16                  us_baw_size;
    oal_uint8                   uc_ampdu_max_num;

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_hmac_user) || (OAL_PTR_NULL == puc_payload))
    {
        OAM_ERROR_LOG3(0, OAM_SF_BA, "{hmac_mgmt_rx_addba_rsp::null param, %d %d %d.}", pst_hmac_vap, pst_hmac_user, puc_payload);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);

    /* ��ȡdevice�ṹ */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_rx_addba_rsp::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /******************************************************************/
    /*       ADDBA Response Frame - Frame Body                        */
    /* ---------------------------------------------------------------*/
    /* | Category | Action | Dialog | Status  | Parameters | Timeout |*/
    /* ---------------------------------------------------------------*/
    /* | 1        | 1      | 1      | 2       | 2          | 2       |*/
    /* ---------------------------------------------------------------*/
    /*                                                                */
    /******************************************************************/

    uc_tidno = (puc_payload[5] & 0x3C) >> 2;
    /* Э��֧��tidΪ0~15,02ֻ֧��tid0~7 */
    if(uc_tidno >= WLAN_TID_MAX_NUM)
    {
        /* ����tid > 7��respֱ�Ӻ��� */
        OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_rx_addba_rsp::addba rsp tid[%d]} token[%d] state[%d]", uc_tidno, puc_payload[2], puc_payload[3]);
        return OAL_SUCC;
    }

    pst_tid  = &(pst_hmac_user->ast_tid_info[uc_tidno]);
    uc_dialog_token = puc_payload[2];

    if (DMAC_BA_INIT == pst_tid->st_ba_tx_info.en_ba_status)
    {
        /* ����DELBA֡ */
        st_action_args.uc_category = MAC_ACTION_CATEGORY_BA;
        st_action_args.uc_action   = MAC_BA_ACTION_DELBA;
        st_action_args.ul_arg1     = uc_tidno;                  /* ������֡��Ӧ��TID�� */
        st_action_args.ul_arg2     = MAC_ORIGINATOR_DELBA;     /* DELBA�У�����ɾ��BA�Ự�ķ���� */
        st_action_args.ul_arg3     = MAC_UNSPEC_QOS_REASON;         /* DELBA�д���ɾ��reason */
        st_action_args.puc_arg5    = pst_hmac_user->st_user_base_info.auc_user_mac_addr;    /* DELBA�д���Ŀ�ĵ�ַ */

        hmac_mgmt_tx_delba(pst_hmac_vap, pst_hmac_user, &st_action_args);
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_rx_addba_rsp::addba rsp is received when ba status is DMAC_BA_INIT.tid[%d]}", uc_tidno);
        return OAL_SUCC;
    }

    if ((DMAC_BA_COMPLETE == pst_tid->st_ba_tx_info.en_ba_status) || (uc_dialog_token != pst_tid->st_ba_tx_info.uc_dialog_token))
    {
        OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_rx_addba_rsp::addba rsp is received whne ba status is DMAC_BA_COMPLETE or uc_dialog_token wrong.tid[%d], status[%d], rsp dialog[%d], req dialog[%d]}",
          uc_tidno, pst_tid->st_ba_tx_info.en_ba_status, uc_dialog_token, pst_tid->st_ba_tx_info.uc_dialog_token);
        return OAL_SUCC;
    }

    /* ֹͣ��ʱ�� */
    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_tid->st_ba_tx_info.st_addba_timer);

    /* ���¼���DMAC���� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_ctx_action_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_rx_addba_rsp::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����¼�ָ�� */
    pst_hmac_to_dmac_crx_sync = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_hmac_to_dmac_crx_sync->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_BA_SYNC,
                       OAL_SIZEOF(dmac_ctx_action_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    /* ��ȡ֡����Ϣ������DMAC��ͬ������д�¼�payload */
    pst_rx_addba_rsp_event = (dmac_ctx_action_event_stru *)(pst_hmac_to_dmac_crx_sync->auc_event_data);
    pst_rx_addba_rsp_event->en_action_category = MAC_ACTION_CATEGORY_BA;
    pst_rx_addba_rsp_event->uc_action          = MAC_BA_ACTION_ADDBA_RSP;
    pst_rx_addba_rsp_event->us_user_idx        = pst_hmac_user->st_user_base_info.us_assoc_id;
    pst_rx_addba_rsp_event->uc_status          = puc_payload[3];
    pst_rx_addba_rsp_event->uc_tidno           = uc_tidno;
    pst_rx_addba_rsp_event->uc_dialog_token    = puc_payload[2];

    if (pst_rx_addba_rsp_event->uc_status != MAC_SUCCESSFUL_STATUSCODE)
    {
        /* ����HMACģ����Ϣ */
        pst_tid->st_ba_tx_info.en_ba_status = DMAC_BA_INIT;

#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
        hmac_tx_ba_session_decr(pst_hmac_vap, uc_tidno);
#else
        hmac_tx_ba_session_decr(pst_mac_device, uc_tidno);
#endif
    }
    else
    {
        /* ֻ��״̬Ϊ�ɹ�ʱ�����б�Ҫ����Щ��Ϣ���ݸ�dmac */
        pst_rx_addba_rsp_event->uc_ba_policy     = ((puc_payload[5] & 0x02) >> 1);
        pst_rx_addba_rsp_event->us_ba_timeout    = puc_payload[7] | (puc_payload[8] << 8);
        pst_rx_addba_rsp_event->en_amsdu_supp    = puc_payload[5] & BIT0;

        us_baw_size      = (oal_uint16)(((puc_payload[5] & 0xC0) >> 6) | (puc_payload[6] << 2));
        if ((0 == us_baw_size) || (us_baw_size > WLAN_AMPDU_TX_MAX_BUF_SIZE))
        {
            us_baw_size = WLAN_AMPDU_TX_MAX_BUF_SIZE;
        }

        uc_ampdu_max_num = (oal_uint8)us_baw_size/WLAN_AMPDU_TX_SCHD_STRATEGY;

        pst_rx_addba_rsp_event->uc_ampdu_max_num = OAL_MAX(uc_ampdu_max_num, 1);
        pst_rx_addba_rsp_event->us_baw_size      = us_baw_size;

        /* ����hmacģ���Ӧ��BA�������Ϣ */
        pst_tid->st_ba_tx_info.en_ba_status     = DMAC_BA_COMPLETE;
        pst_tid->st_ba_tx_info.uc_addba_attemps = 0;
        /*lint -e502*/
        if (pst_rx_addba_rsp_event->en_amsdu_supp && pst_hmac_vap->en_amsdu_ampdu_active)
        {
            HMAC_USER_SET_AMSDU_SUPPORT(pst_hmac_user, uc_tidno);
        }
        else
        {
            HMAC_USER_SET_AMSDU_NOT_SUPPORT(pst_hmac_user, uc_tidno);
        }
        /*lint +e502*/
    }

    /* �ַ� */
    frw_event_dispatch_event(pst_event_mem);

    /* �ͷ��¼��ڴ� */
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_rx_delba
 ��������  : �ӿտڽ���DEL_BA֡�Ĵ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��14��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_mgmt_rx_delba(
                hmac_vap_stru    *pst_hmac_vap,
                hmac_user_stru   *pst_hmac_user,
                oal_uint8        *puc_payload)
{
    frw_event_mem_stru           *pst_event_mem;      /* �����¼����ص��ڴ�ָ�� */
    frw_event_stru               *pst_hmac_to_dmac_crx_sync;
    dmac_ctx_action_event_stru   *pst_wlan_crx_action;
    mac_device_stru              *pst_device;
    hmac_tid_stru                *pst_tid;
    oal_uint8                     uc_tid;
    oal_uint8                     uc_initiator;
    oal_uint16                    us_reason;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_hmac_user) || (OAL_PTR_NULL == puc_payload)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_BA, "{hmac_mgmt_rx_delba::null param, %d %d %d.}", pst_hmac_vap, pst_hmac_user, puc_payload);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡdevice�ṹ */
    pst_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_mgmt_rx_delba::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /************************************************/
    /*       DELBA Response Frame - Frame Body      */
    /* -------------------------------------------- */
    /* | Category | Action | Parameters | Reason  | */
    /* -------------------------------------------- */
    /* | 1        | 1      | 2          | 2       | */
    /* -------------------------------------------- */
    /*                                              */
    /************************************************/
    uc_tid       = (puc_payload[3] & 0xF0) >> 4;
    uc_initiator = (puc_payload[3] & 0x08) >> 3;
    us_reason    = (puc_payload[4] & 0xFF) | ((puc_payload[5] << 8) & 0xFF00);

    /* tid��������������Խ�� */
    if (uc_tid >= WLAN_TID_MAX_NUM)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_mgmt_rx_delba::delba receive failed, tid %d overflow.}", uc_tid);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }
    pst_tid      = &(pst_hmac_user->ast_tid_info[uc_tid]);

    OAM_WARNING_LOG3(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_mgmt_rx_delba::receive delba from peer sta, tid[%d], uc_initiator[%d], reason[%d].}",
      uc_tid, uc_initiator, us_reason);

    /* ����BA���ͻỰ */
    if (MAC_RECIPIENT_DELBA == uc_initiator)
    {
        if (DMAC_BA_INIT == pst_tid->st_ba_tx_info.en_ba_status)
        {
            return OAL_SUCC;
        }

        pst_hmac_user->auc_ba_flag[uc_tid]  = 0;

        /* ��ԭ����AMPDU��AMSDU��֧����� */
        HMAC_USER_SET_AMSDU_SUPPORT(pst_hmac_user, uc_tid);

#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
        hmac_tx_ba_session_decr(pst_hmac_vap, pst_hmac_user->ast_tid_info[uc_tid].uc_tid_no);
#else
        hmac_tx_ba_session_decr(pst_device, pst_hmac_user->ast_tid_info[uc_tid].uc_tid_no);
#endif
    }
    else   /* ����BA���ջỰ */
    {
        hmac_ba_reset_rx_handle(pst_device, &pst_hmac_user->ast_tid_info[uc_tid].pst_ba_rx_info, uc_tid, OAL_FALSE);
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA,
                      "{hmac_mgmt_rx_delba::rcv rx dir del ba.}\r\n");
    }

    /* ���¼���DMAC���� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_ctx_action_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_mgmt_rx_delba::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����¼�ָ�� */
    pst_hmac_to_dmac_crx_sync = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_hmac_to_dmac_crx_sync->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_BA_SYNC,
                       OAL_SIZEOF(dmac_ctx_action_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_hmac_vap->st_vap_base_info.uc_chip_id,
                       pst_hmac_vap->st_vap_base_info.uc_device_id,
                       pst_hmac_vap->st_vap_base_info.uc_vap_id);

    /*��д�¼�payload */
    pst_wlan_crx_action = (dmac_ctx_action_event_stru *)(pst_hmac_to_dmac_crx_sync->auc_event_data);
    pst_wlan_crx_action->en_action_category  = MAC_ACTION_CATEGORY_BA;
    pst_wlan_crx_action->uc_action           = MAC_BA_ACTION_DELBA;
    pst_wlan_crx_action->us_user_idx         = pst_hmac_user->st_user_base_info.us_assoc_id;

    pst_wlan_crx_action->uc_tidno            = uc_tid;
    pst_wlan_crx_action->uc_initiator        = uc_initiator;

    /* �ַ� */
    frw_event_dispatch_event(pst_event_mem);

    /* �ͷ��¼��ڴ� */
    FRW_EVENT_FREE(pst_event_mem);

    /* DELBA�¼��ȴ����ٸ�״̬,��ֹaddba req�ȴ��� */
    if (MAC_RECIPIENT_DELBA == uc_initiator)
    {
        pst_tid->st_ba_tx_info.en_ba_status = DMAC_BA_INIT;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_tx_addba_timeout
 ��������  : ����ADDBA req֡��ʱ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��22��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_mgmt_tx_addba_timeout(oal_void *p_arg)
{
    hmac_vap_stru                      *pst_vap = OAL_PTR_NULL;         /* vapָ�� */
    oal_uint8                          *puc_da;                         /* �����û�Ŀ�ĵ�ַ��ָ�� */
    hmac_user_stru                     *pst_hmac_user;
    mac_action_mgmt_args_stru           st_action_args;
    dmac_ba_alarm_stru                 *pst_alarm_data;

    if (OAL_PTR_NULL == p_arg)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BA, "{hmac_mgmt_tx_addba_timeout::p_arg null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alarm_data = (dmac_ba_alarm_stru *)p_arg;

    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(pst_alarm_data->us_mac_user_idx);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BA, "{hmac_mgmt_tx_addba_timeout::pst_hmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    puc_da  = pst_hmac_user->st_user_base_info.auc_user_mac_addr;

    pst_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_alarm_data->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_BA, "{hmac_mgmt_tx_addba_timeout::pst_hmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����DELBA֡ */
    st_action_args.uc_category = MAC_ACTION_CATEGORY_BA;
    st_action_args.uc_action   = MAC_BA_ACTION_DELBA;
    st_action_args.ul_arg1     = pst_alarm_data->uc_tid;        /* ������֡��Ӧ��TID�� */
    st_action_args.ul_arg2     = MAC_ORIGINATOR_DELBA;         /* DELBA�У�����ɾ��BA�Ự�ķ���� */
    st_action_args.ul_arg3     = MAC_QSTA_TIMEOUT;                  /* DELBA�д���ɾ��reason */
    st_action_args.puc_arg5    = puc_da;                        /* DELBA�д���Ŀ�ĵ�ַ */

    hmac_mgmt_tx_delba(pst_vap, pst_hmac_user, &st_action_args);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_tx_ampdu_start
 ��������  : ��������AMPDU����Ҫ�Ĳ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��26��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_mgmt_tx_ampdu_start(
                hmac_vap_stru              *pst_hmac_vap,
                hmac_user_stru             *pst_hmac_user,
                mac_priv_req_args_stru     *pst_priv_req)
{
    frw_event_mem_stru         *pst_event_mem;      /* �����¼����ص��ڴ�ָ�� */
    frw_event_stru             *pst_crx_priv_req_event;
    mac_priv_req_args_stru     *pst_rx_ampdu_start_event;
    oal_uint8                   uc_tidno;
    hmac_tid_stru              *pst_tid;
    oal_uint32                  ul_ret;

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_hmac_user) || (OAL_PTR_NULL == pst_priv_req))
    {
        OAM_ERROR_LOG3(0, OAM_SF_AMPDU, "{hmac_mgmt_tx_ampdu_start::param null, %d %d %d.}", pst_hmac_vap, pst_hmac_user, pst_priv_req);
        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_tidno = pst_priv_req->uc_arg1;
    pst_tid  = &(pst_hmac_user->ast_tid_info[uc_tidno]);

    /* AMPDUΪNORMAL ACKʱ����Ӧ��BA�Ựû�н������򷵻� */
    if (WLAN_TX_NORMAL_ACK == pst_priv_req->uc_arg3)
    {
        if (DMAC_BA_INIT == pst_tid->st_ba_tx_info.en_ba_status)
        {
            OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "{hmac_mgmt_tx_ampdu_start::normal ack but ba session is not build.}");
            return OAL_SUCC;
        }
    }

    /* ���¼���DMAC���� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(mac_priv_req_args_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "{hmac_mgmt_tx_ampdu_start::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����¼�ָ�� */
    pst_crx_priv_req_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_crx_priv_req_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_PRIV_REQ,
                       OAL_SIZEOF(mac_priv_req_args_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_hmac_vap->st_vap_base_info.uc_chip_id,
                       pst_hmac_vap->st_vap_base_info.uc_device_id,
                       pst_hmac_vap->st_vap_base_info.uc_vap_id);

    /* ��ȡ����AMPDU�Ĳ�������dmac�������� */
    pst_rx_ampdu_start_event = (mac_priv_req_args_stru *)(pst_crx_priv_req_event->auc_event_data);
    pst_rx_ampdu_start_event->uc_type = MAC_A_MPDU_START;
    pst_rx_ampdu_start_event->uc_arg1 = pst_priv_req->uc_arg1;
    pst_rx_ampdu_start_event->uc_arg2 = pst_priv_req->uc_arg2;
    pst_rx_ampdu_start_event->uc_arg3 = pst_priv_req->uc_arg3;
    pst_rx_ampdu_start_event->us_user_idx = pst_hmac_user->st_user_base_info.us_assoc_id;   /* ���������Դ�ص����� */

    /* �ַ� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);

    /* �ͷ��¼��ڴ� */
    FRW_EVENT_FREE(pst_event_mem);

    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_tx_ampdu_end
 ��������  : ���ùر�AMPDU
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��7��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_mgmt_tx_ampdu_end(
                hmac_vap_stru              *pst_hmac_vap,
                hmac_user_stru             *pst_hmac_user,
                mac_priv_req_args_stru     *pst_priv_req)
{

    frw_event_mem_stru         *pst_event_mem;      /* �����¼����ص��ڴ�ָ�� */
    frw_event_stru             *pst_crx_priv_req_event;
    mac_priv_req_args_stru     *pst_rx_ampdu_end_event;
    oal_uint32                  ul_ret;

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_hmac_user) || (OAL_PTR_NULL == pst_priv_req))
    {
        OAM_ERROR_LOG3(0, OAM_SF_AMPDU, "{hmac_mgmt_tx_ampdu_end::param null, %d %d %d.}", pst_hmac_vap, pst_hmac_user, pst_priv_req);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���¼���DMAC���� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(mac_priv_req_args_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "{hmac_mgmt_tx_ampdu_end::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����¼�ָ�� */
    pst_crx_priv_req_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_crx_priv_req_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_PRIV_REQ,
                       OAL_SIZEOF(mac_priv_req_args_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_hmac_vap->st_vap_base_info.uc_chip_id,
                       pst_hmac_vap->st_vap_base_info.uc_device_id,
                       pst_hmac_vap->st_vap_base_info.uc_vap_id);

    /* ��ȡ����AMPDU�Ĳ�������dmac�������� */
    pst_rx_ampdu_end_event = (mac_priv_req_args_stru *)(pst_crx_priv_req_event->auc_event_data);
    pst_rx_ampdu_end_event->uc_type = MAC_A_MPDU_END;              /* ���� */
    pst_rx_ampdu_end_event->uc_arg1 = pst_priv_req->uc_arg1;        /* tid no */
    pst_rx_ampdu_end_event->us_user_idx = pst_hmac_user->st_user_base_info.us_assoc_id;   /* ���������Դ�ص����� */

    /* �ַ� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);


    /* �ͷ��¼��ڴ� */
    FRW_EVENT_FREE(pst_event_mem);

    return ul_ret;
}


/*****************************************************************************
 �� �� ��  : hmac_tx_mgmt_send_event
 ��������  : ���͹���֡���¼�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��29��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_tx_mgmt_send_event(mac_vap_stru *pst_vap, oal_netbuf_stru *pst_mgmt_frame, oal_uint16 us_frame_len)
{
    frw_event_mem_stru   *pst_event_mem;
    frw_event_stru       *pst_event;
    oal_uint32            ul_return;
    dmac_tx_event_stru   *pst_ctx_stru;

    if (OAL_PTR_NULL == pst_vap || OAL_PTR_NULL == pst_mgmt_frame)
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{hmac_tx_mgmt_send_event::param null, %d %d.}", pst_vap, pst_mgmt_frame);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���¼���DMAC,��DMAC�������VAP���� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_tx_mgmt_send_event::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    DMAC_WLAN_CTX_EVENT_SUB_TYPE_MGMT,
                    OAL_SIZEOF(dmac_tx_event_stru),
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_vap->uc_chip_id,
                    pst_vap->uc_device_id,
                    pst_vap->uc_vap_id);

    pst_ctx_stru                = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_ctx_stru->pst_netbuf    = pst_mgmt_frame;
    pst_ctx_stru->us_frame_len  = us_frame_len;

    ul_return = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_return)
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_tx_mgmt_send_event::frw_event_dispatch_event failed[%d].}", ul_return);
        FRW_EVENT_FREE(pst_event_mem);
        return ul_return;
    }

    /* �ͷ��¼� */
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_reset_psm
 ��������  : �յ���֤���� ��������ʱ �����û��Ľ���״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��17��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��1��26��
    ��    ��   : g00306640
    �޸�����   : ����keepalive����
*****************************************************************************/
oal_uint32  hmac_mgmt_reset_psm(mac_vap_stru *pst_vap, oal_uint16 us_user_id)
{
    frw_event_mem_stru   *pst_event_mem;
    frw_event_stru       *pst_event;
    oal_uint16           *pus_user_id;
    hmac_user_stru       *pst_hmac_user;

    if (OAL_PTR_NULL == pst_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{hmac_mgmt_reset_psm::pst_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* ������ֱ�������õ�һЩ����������Ҫ�ٴ�ͬ�� */
    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(us_user_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_user))
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_PWR, "{hmac_mgmt_reset_psm::pst_hmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(oal_uint16));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_PWR, "{hmac_mgmt_reset_psm::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    DMAC_WLAN_CTX_EVENT_SUB_TYPE_RESET_PSM,
                    OAL_SIZEOF(oal_uint16),
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_vap->uc_chip_id,
                    pst_vap->uc_device_id,
                    pst_vap->uc_vap_id);

    pus_user_id = (oal_uint16 *)pst_event->auc_event_data;

    *pus_user_id = us_user_id;

    frw_event_dispatch_event(pst_event_mem);

    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_sa_query_del_user
 ��������  : ��ʼSA Query timer1��ʱɾ��user
 �������  : pst_mac_vap:�Ҵ�user��vap
             puc_addr:��Ҫɾ����user mac��ַ
 �������  : ��
 �� �� ֵ  : OAL_SUCC:ɾ���û��ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��21��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���


*****************************************************************************/

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
OAL_STATIC oal_uint32 hmac_sa_query_del_user(mac_vap_stru *pst_mac_vap, hmac_user_stru  *pst_hmac_user)
{
    wlan_vap_mode_enum_uint8      en_vap_mode;
    hmac_vap_stru                *pst_hmac_vap  = OAL_PTR_NULL;
    oal_uint32                    ul_ret;
    mac_sa_query_stru            *pst_sa_query_info;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_hmac_user))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PMF, "{hmac_sa_query_del_user::param null, %d %d.}", pst_mac_vap, pst_hmac_user);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_device_id, OAM_SF_PMF, "{hmac_sa_query_del_user::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* pending SA Query requests ���������� & sa query���̿�ʼʱ������ */
    pst_sa_query_info = &pst_hmac_user->st_sa_query_info;
    pst_sa_query_info->ul_sa_query_count      = 0;
    pst_sa_query_info->ul_sa_query_start_time = 0;

    /* �޸� state & ɾ�� user */
    en_vap_mode = pst_mac_vap->en_vap_mode;
    switch (en_vap_mode)
    {
        case WLAN_VAP_MODE_BSS_AP:
            {
                /* ���¼��ϱ��ںˣ��Ѿ�ȥ����ĳ��STA */
                hmac_handle_disconnect_rsp_ap(pst_hmac_vap,pst_hmac_user);
            }
            break;

         case WLAN_VAP_MODE_BSS_STA:
            {
                hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_STA_FAKE_UP);

                /* �ϱ��ں�sta�Ѿ���ĳ��apȥ���� */
                hmac_sta_handle_disassoc_rsp(pst_hmac_vap, MAC_DEAUTH_LV_SS);
            }
             break;
         default:
             break;
    }

    /* ɾ��user */
    ul_ret = hmac_user_del(&pst_hmac_vap->st_vap_base_info, pst_hmac_user);
    if( OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_device_id, OAM_SF_PMF, "{hmac_sa_query_del_user::hmac_user_del failed[%d].}", ul_ret);
        return OAL_FAIL;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_send_sa_query_req
 ��������  : hmac_start_sa_query���¼�������û������timer�Ĺ���
 �������  : pst_mac_vap:����SA��ѯ��mac vap�ṹ��
             puc_da:Ŀ��user��mac ��ַ
             en_is_protected:SA Query֡�ļ��ܱ�־λ

 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��21��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

 *****************************************************************************/
OAL_STATIC oal_uint32 hmac_send_sa_query_req(mac_vap_stru *pst_mac_vap,
                                                     hmac_user_stru  *pst_hmac_user,
                                                     oal_bool_enum_uint8 en_is_protected,
                                                     oal_uint16 us_init_trans_id)
{
    oal_uint16                    us_sa_query_len = 0;
    oal_netbuf_stru              *pst_sa_query    = OAL_PTR_NULL;
    mac_tx_ctl_stru              *pst_tx_ctl      = OAL_PTR_NULL;
    oal_uint32                    ul_ret;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_hmac_user))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PMF, "{hmac_send_sa_query_req::param null, %d %d.}", pst_mac_vap, pst_hmac_user);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����SA Query ֡�ռ� */
    pst_sa_query = (oal_netbuf_stru *)OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if(OAL_PTR_NULL == pst_sa_query)
    {
       OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PMF, "{hmac_send_sa_query_req::pst_sa_query null.}");
       return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* ���� trans id */
    pst_hmac_user->st_sa_query_info.us_sa_query_trans_id = us_init_trans_id + 1;

    /* ����sa query request������ */
    pst_hmac_user->st_sa_query_info.ul_sa_query_count += 1;

    /* ��װSA Query request֡*/
    OAL_MEMZERO(oal_netbuf_cb(pst_sa_query), OAL_NETBUF_CB_SIZE());
    us_sa_query_len = hmac_encap_sa_query_req(pst_mac_vap,
                                             (oal_uint8 *)OAL_NETBUF_HEADER(pst_sa_query),
                                             pst_hmac_user->st_user_base_info.auc_user_mac_addr,
                                             pst_hmac_user->st_sa_query_info.us_sa_query_trans_id);

    /* ��������֡���� */
    if (OAL_TRUE == en_is_protected)
    {
        mac_set_protectedframe((oal_uint8 *)OAL_NETBUF_HEADER(pst_sa_query));
    }

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_sa_query); /* ��ȡcb�ṹ�� */
    pst_tx_ctl->us_mpdu_len     = us_sa_query_len;               /* dmac������Ҫ��mpdu���� */
    pst_tx_ctl->us_tx_user_idx  = 0xffff;                        /* ���������Ҫ��ȡuser�ṹ�� */

    oal_netbuf_put(pst_sa_query, us_sa_query_len);


    /* Buffer this frame in the Memory Queue for transmission */
    ul_ret = hmac_tx_mgmt_send_event(pst_mac_vap, pst_sa_query, us_sa_query_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_sa_query);
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PMF, "{hmac_send_sa_query_req::hmac_tx_mgmt_send_event failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_pmf_check_err_code
 ��������  : �ж��Ƿ���յ���ȥ����ȥ��֤֡����PMF���ԵĴ���
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC: �������PMF���ԵĴ���(�翪��sa query����)
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���


*****************************************************************************/
oal_uint32 hmac_pmf_check_err_code(mac_user_stru *pst_user_base_info, oal_bool_enum_uint8 en_is_protected, oal_uint8 *puc_mac_hdr)
{
    oal_bool_enum_uint8 en_aim_err_code = OAL_FALSE;
    oal_uint16 us_err_code = MAC_UNSPEC_REASON;

    us_err_code = OAL_MAKE_WORD16(puc_mac_hdr[MAC_80211_FRAME_LEN], puc_mac_hdr[MAC_80211_FRAME_LEN + 1]);
    en_aim_err_code = ((MAC_NOT_AUTHED == us_err_code) || (MAC_NOT_ASSOCED == us_err_code)) ? OAL_TRUE : OAL_FALSE;

    if ((OAL_TRUE  == pst_user_base_info->st_cap_info.bit_pmf_active) &&
        (OAL_TRUE  == en_aim_err_code) &&
        (OAL_FALSE == en_is_protected))
    {
        return OAL_SUCC;
    }

    return OAL_FAIL;

}

/*****************************************************************************
 �� �� ��  : hmac_sa_query_interval_timeout
 ��������  : ��ʼSA Query timer2��ʱ����
 �������  : p_arg:timer2��ʱ������νṹ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC:��ʱ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��21��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���


*****************************************************************************/
oal_uint32 hmac_sa_query_interval_timeout(oal_void *p_arg)
{
    hmac_interval_timer_stru      *pst_interval_timer_arg = OAL_PTR_NULL;
    oal_uint32                     ul_relt;

    if (OAL_PTR_NULL == p_arg)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_sa_query_interval_timeout::p_arg null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_interval_timer_arg = (hmac_interval_timer_stru *)p_arg;

    if ((OAL_PTR_NULL == pst_interval_timer_arg->pst_hmac_user) ||
       (MAC_USER_STATE_ASSOC != pst_interval_timer_arg->pst_hmac_user->st_user_base_info.en_user_asoc_state))
    {
        OAM_ERROR_LOG0(pst_interval_timer_arg->pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_sa_query_interval_timeout::invalid param.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �ж��Ƿ�ʱ */
    if(3 <= pst_interval_timer_arg->pst_hmac_user->st_sa_query_info.ul_sa_query_count)
    {
        /*change state & ul_sa_query_count=0*/
        OAM_INFO_LOG0(pst_interval_timer_arg->pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_sa_query_interval_timeout::Deleting user.}");
        ul_relt = hmac_sa_query_del_user(pst_interval_timer_arg->pst_mac_vap, pst_interval_timer_arg->pst_hmac_user);
        if (OAL_SUCC != ul_relt)
        {
            OAM_ERROR_LOG1(pst_interval_timer_arg->pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                           "{hmac_sa_query_interval_timeout::hmac_sa_query_del_user failed[%d].}", ul_relt);
            return OAL_ERR_CODE_PMF_SA_QUERY_DEL_USER_FAIL;
        }
        return OAL_SUCC;
    }

    /* ѭ������sa query request */
    ul_relt = hmac_send_sa_query_req(pst_interval_timer_arg->pst_mac_vap,
                                     pst_interval_timer_arg->pst_hmac_user,
                                     pst_interval_timer_arg->en_is_protected,
                                     pst_interval_timer_arg->us_trans_id);
    if (OAL_SUCC != ul_relt)
    {
       OAM_ERROR_LOG1(pst_interval_timer_arg->pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                           "{hmac_sa_query_interval_timeout::hmac_send_sa_query_req failed[%d].}", ul_relt);
       return OAL_ERR_CODE_PMF_SA_QUERY_REQ_SEND_FAIL;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_start_sa_query
 ��������  : ��ʼSA Query ��ѯ����
 �������  : pst_mac_vap:����SA��ѯ��mac vap�ṹ��
             puc_da:Ŀ��user��mac ��ַ
             en_is_protected:SA Query֡�ļ��ܱ�־λ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��21��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���


*****************************************************************************/
oal_uint32 hmac_start_sa_query(mac_vap_stru *pst_mac_vap, hmac_user_stru  *pst_hmac_user, oal_bool_enum_uint8 en_is_protected)
{
    hmac_interval_timer_stru     *pst_interval_timer_arg;
    oal_uint16                    us_retry_timeout;
    hmac_vap_stru                *pst_hmac_vap    = OAL_PTR_NULL;
    oal_uint32                    ul_ret;
    oal_uint16                    us_init_trans_id;


    /* ����ж� */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_hmac_user))
    {
       OAM_ERROR_LOG2(0, OAM_SF_ANY, "{hmac_start_sa_query::param null, %d %d.}", pst_mac_vap, pst_hmac_user);
       return OAL_ERR_CODE_PTR_NULL;
    }

    /* �ж�vap����pmf���� */
    if (OAL_TRUE != pst_hmac_user->st_user_base_info.st_cap_info.bit_pmf_active)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_start_sa_query::bit_pmf_active is down.}");
        return OAL_ERR_CODE_PMF_DISABLED;
    }

    /* �����ظ�����SA Query���� */
    if (0 != pst_hmac_user->st_sa_query_info.ul_sa_query_count)
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_start_sa_query::SA Query is already in process.}");
        return OAL_SUCC;
    }

    /* ���hmac vap �ṹָ�� */
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_start_sa_query::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ó�ʼtrans_id */
    us_init_trans_id = (oal_uint16)OAL_TIME_GET_STAMP_MS();

    /* ����timer��ʱ������� */
    pst_interval_timer_arg = (hmac_interval_timer_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(hmac_interval_timer_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_interval_timer_arg)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_start_sa_query::pst_interval_timer_arg null.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }
    pst_interval_timer_arg->pst_mac_vap     = pst_mac_vap;
    pst_interval_timer_arg->pst_hmac_user   = pst_hmac_user;
    pst_interval_timer_arg->en_is_protected = en_is_protected;
    pst_interval_timer_arg->us_trans_id     = us_init_trans_id;
    us_retry_timeout = (oal_uint16)mac_mib_get_dot11AssociationSAQueryRetryTimeout(pst_mac_vap);

    /* ��¼sa query���̿�ʼʱ��,��λms */
    pst_hmac_user->st_sa_query_info.ul_sa_query_start_time = (oal_uint32)OAL_TIME_GET_STAMP_MS();
    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_start_sa_query::Start a SA query process.}");

    /* ���ü����ʱ�� */
    FRW_TIMER_CREATE_TIMER(&(pst_hmac_user->st_sa_query_info.st_sa_query_interval_timer),
                           hmac_sa_query_interval_timeout,
                           us_retry_timeout,
                           pst_interval_timer_arg,
                           OAL_TRUE,
                           OAM_MODULE_ID_HMAC,
                           pst_mac_vap->ul_core_id);

    /* ����SA Query request����ʼ��ѯ���� */
    ul_ret = hmac_send_sa_query_req(pst_mac_vap, pst_hmac_user, en_is_protected, us_init_trans_id);
    if (OAL_SUCC != ul_ret)
    {
       OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_start_sa_query::hmac_send_sa_query_req failed[%d].}", ul_ret);
       return OAL_ERR_CODE_PMF_SA_QUERY_REQ_SEND_FAIL;
    }


    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_send_sa_query_rsq
 ��������  : ����SA query response֡
 �������  : pst_mac_vap:����SA query responsed��mac vap�ṹ��
             pst_hdr:���յ�sa query request֡��֡ͷָ��
             en_is_protected:SA Query֡�ļ��ܱ�־λ
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��21��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���


*****************************************************************************/
oal_void  hmac_send_sa_query_rsp(mac_vap_stru *pst_mac_vap, oal_uint8 *pst_hdr, oal_bool_enum_uint8 en_is_protected)
{
    oal_uint16                    us_sa_query_len = 0;
    oal_netbuf_stru              *pst_sa_query    = 0;
    mac_tx_ctl_stru              *pst_tx_ctl      = OAL_PTR_NULL;
    oal_uint32                    ul_ret;

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == pst_hdr)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{hmac_send_sa_query_rsp::param null, %d %d.}", pst_mac_vap, pst_hdr);
        return;
    }
    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_send_sa_query_rsp::AP ready to TX a sa query rsp.}");

    pst_sa_query = (oal_netbuf_stru *)OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if (OAL_PTR_NULL == pst_sa_query)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_send_sa_query_rsp::pst_sa_query null.}");
        return;
    }

    OAL_MEMZERO(oal_netbuf_cb(pst_sa_query), OAL_NETBUF_CB_SIZE());
    us_sa_query_len = hmac_encap_sa_query_rsp(pst_mac_vap, pst_hdr, (oal_uint8 *)OAL_NETBUF_HEADER(pst_sa_query));

    /*��������֡����*/
    if (OAL_TRUE == en_is_protected)
    {
        mac_set_protectedframe((oal_uint8 *)OAL_NETBUF_HEADER(pst_sa_query));
    }

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_sa_query); /* ��ȡcb�ṹ�� */
    pst_tx_ctl->us_mpdu_len     = us_sa_query_len;               /* dmac������Ҫ��mpdu���� */
    pst_tx_ctl->us_tx_user_idx  = 0xffff;                        /* ���������Ҫ��ȡuser�ṹ�� */

    oal_netbuf_put(pst_sa_query, us_sa_query_len);

    /* Buffer this frame in the Memory Queue for transmission */
    ul_ret = hmac_tx_mgmt_send_event(pst_mac_vap, pst_sa_query, us_sa_query_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_sa_query);
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_send_sa_query_rsp::hmac_tx_mgmt_send_event failed[%d].}", ul_ret);
    }

    return;
}
#endif
/*****************************************************************************
 �� �� ��  : hmac_mgmt_send_deauth_frame
 ��������  : ����ȥ��֤֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_mgmt_send_deauth_frame(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_da, oal_uint16 us_err_code, oal_bool_enum_uint8 en_is_protected)
{
    oal_uint16        us_deauth_len = 0;
    oal_netbuf_stru  *pst_deauth    = 0;
    mac_tx_ctl_stru  *pst_tx_ctl;
    oal_uint32        ul_ret;
    hmac_vap_stru    *pst_hmac_vap;
    oal_uint16        us_user_idx             = 0xffff;

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_da)
    {
        OAM_ERROR_LOG2(0, OAM_SF_AUTH, "{hmac_mgmt_send_deauth_frame::param null, %d %d.}", pst_mac_vap, pst_mac_vap);
        return;
    }

    /* DTS2015120203304: ����ȥ��֤ǰ��ȷ��vap���ڹ���״̬ */
    if (MAC_VAP_STATE_BUTT == pst_mac_vap->en_vap_state)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_AUTH, "{hmac_mgmt_send_deauth_frame:: vap has been down/del, vap_state[%d].}", pst_mac_vap->en_vap_state);
        return;
    }

    pst_deauth = (oal_netbuf_stru *)OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);

    OAL_MEM_NETBUF_TRACE(pst_deauth, OAL_TRUE);

    if(OAL_PTR_NULL == pst_deauth)
    {
        /* Reserved Memory pool tried for high priority deauth frames */
        pst_deauth = (oal_netbuf_stru *)OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF,WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
        if(OAL_PTR_NULL == pst_deauth)
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_AUTH, "{hmac_mgmt_send_deauth_frame::pst_deauth null.}");
            return;
        }
    }

    OAL_MEMZERO(oal_netbuf_cb(pst_deauth), OAL_NETBUF_CB_SIZE());

    us_deauth_len = hmac_mgmt_encap_deauth(pst_mac_vap, (oal_uint8 *)OAL_NETBUF_HEADER(pst_deauth), puc_da, us_err_code);
    if (0 == us_deauth_len)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_AUTH, "{hmac_mgmt_send_deauth_frame:: us_deauth_len = 0.}");
        oal_netbuf_free(pst_deauth);
        return;
    }
    oal_netbuf_put(pst_deauth, us_deauth_len);

    /* MIB variables related to deauthentication are updated */
    mac_mib_set_DeauthenticateReason(pst_mac_vap, us_err_code);
    mac_mib_set_DeauthenticateStation(pst_mac_vap, puc_da);

    /* ���ӷ���ȥ��֤֡ʱ��ά����Ϣ */
    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_AUTH,
		      "{hmac_mgmt_send_deauth_frame:: send deauth frame to %2x:XX:XX:XX:%2x:%2x, status code[%d]}",
		       puc_da[0], puc_da[4], puc_da[5],us_err_code);

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_deauth);                              /* ��ȡcb�ṹ�� */
    pst_tx_ctl->us_mpdu_len   = us_deauth_len;                                      /* dmac������Ҫ��mpdu���� */
    pst_tx_ctl->us_tx_user_idx              = 0xffff;  /* ���������Ҫ��ȡuser�ṹ�� */

    /* Buffer this frame in the Memory Queue for transmission */
    ul_ret = hmac_tx_mgmt_send_event(pst_mac_vap, pst_deauth, us_deauth_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_deauth);

        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_AUTH, "{hmac_mgmt_send_deauth_frame::hmac_tx_mgmt_send_event failed[%d].}", ul_ret);
    }

    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, puc_da, &us_user_idx);
    	if (OAL_SUCC != ul_ret)
    	{
    		OAM_WARNING_LOG1(0, OAM_SF_AUTH, "{hmac_mgmt_send_deauth_frame::mac_vap_find_user_by_macaddr failed.err code[%u].}", ul_ret);
    		return;
    	}
    	pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    	if (OAL_PTR_NULL == pst_hmac_vap)
    	{
    		OAM_ERROR_LOG1(0, OAM_SF_AUTH, "{hmac_mgmt_send_deauth_frame::mac_res_get_hmac_vap fail.vap_id[%u]}",pst_mac_vap->uc_vap_id);
                  return;
    	}
    	hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_STA_FAKE_UP);
    }

}
/*****************************************************************************
 �� �� ��  : hmac_config_send_deauth
 ��������  : ��������ȥ��֤1���û�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_config_send_deauth(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_da)
{
    hmac_user_stru                 *pst_hmac_user;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_da))
    {
        OAM_ERROR_LOG2(0, OAM_SF_AUTH, "{hmac_config_send_deauth::param null, %d %d.}", pst_mac_vap, puc_da);
        return OAL_ERR_CODE_PTR_NULL;
    }


    pst_hmac_user = mac_vap_get_hmac_user_by_addr(pst_mac_vap, puc_da);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_AUTH, "{hmac_config_send_deauth::pst_hmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (MAC_USER_STATE_ASSOC != pst_hmac_user->st_user_base_info.en_user_asoc_state)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_AUTH, "{hmac_config_send_deauth::the user is unassociated.}");
        return OAL_FAIL;
    }


    /* ��ȥ��֤֡ */
    hmac_mgmt_send_deauth_frame(pst_mac_vap, puc_da, MAC_AUTH_NOT_VALID, OAL_FALSE);

    /* ɾ���û� */
    hmac_user_del(pst_mac_vap, pst_hmac_user);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_send_disassoc_frame
 ��������  : ����ȥ����֡
 �������  : vapָ��, DA, errcode
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��2��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_mgmt_send_disassoc_frame(mac_vap_stru *pst_mac_vap,oal_uint8 *puc_da, oal_uint16 us_err_code, oal_bool_enum_uint8 en_is_protected)
{
    oal_uint16        us_disassoc_len = 0;
    oal_netbuf_stru  *pst_disassoc    = 0;
    mac_tx_ctl_stru  *pst_tx_ctl;
    oal_uint32        ul_ret;
    hmac_vap_stru    *pst_hmac_vap;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint32        ul_pedding_data = 0;
#endif

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_da)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ASSOC, "{hmac_mgmt_send_disassoc_frame::param null, %d %d.}", pst_mac_vap, pst_mac_vap);
        return;
    }

    /* DTS2015120203304: ����ȥ����ǰ��ȷ��vap���ڹ���״̬ */
    if (MAC_VAP_STATE_BUTT == pst_mac_vap->en_vap_state)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC, "{hmac_mgmt_send_disassoc_frame:: vap has been down/del, vap_state[%d].}", pst_mac_vap->en_vap_state);
        return;
    }

    pst_disassoc = (oal_netbuf_stru *)OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);

    if(OAL_PTR_NULL == pst_disassoc)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC, "{hmac_mgmt_send_disassoc_frame::pst_disassoc null.}");
        return;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    hmac_config_scan_abort(pst_mac_vap, OAL_SIZEOF(oal_uint32), (oal_uint8 *)&ul_pedding_data);
#endif

    OAL_MEM_NETBUF_TRACE(pst_disassoc, OAL_TRUE);

    OAL_MEMZERO(oal_netbuf_cb(pst_disassoc), OAL_NETBUF_CB_SIZE());

    us_disassoc_len = hmac_mgmt_encap_disassoc(pst_mac_vap, (oal_uint8 *)OAL_NETBUF_HEADER(pst_disassoc), puc_da, us_err_code);
    if (0 == us_disassoc_len)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC, "{hmac_mgmt_send_disassoc_frame:: us_disassoc_len = 0.}");
        oal_netbuf_free(pst_disassoc);
        return;
    }

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    if (OAL_TRUE == en_is_protected)
    {
        mac_set_protectedframe((oal_uint8 *)OAL_NETBUF_HEADER(pst_disassoc));
    }
#endif

    mac_mib_set_DisassocReason(pst_mac_vap, us_err_code);
    mac_mib_set_DisassocStation(pst_mac_vap, puc_da);

    /* ���ӷ���ȥ����֡ʱ��ά����Ϣ */
    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                     "{hmac_mgmt_send_disassoc_frame::Because of err_code[%d], send disassoc frame to dest addr, da[%2x:xx:xx:xx:%2x:%2x].}",
                    us_err_code, puc_da[0], puc_da[4], puc_da[5]);

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_disassoc);
    pst_tx_ctl->us_mpdu_len  = us_disassoc_len;
    /* ��д�Ƿ�ֵ,�������֮���ȡ�û�ΪNULL,ֱ���ͷ�ȥ��֤֡  */
    pst_tx_ctl->us_tx_user_idx              = 0xffff;

    oal_netbuf_put(pst_disassoc, us_disassoc_len);

    /* ���뷢�Ͷ��� */
    ul_ret = hmac_tx_mgmt_send_event(pst_mac_vap, pst_disassoc, us_disassoc_len);

    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
        if (OAL_PTR_NULL == pst_hmac_vap)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC, "{hmac_mgmt_send_disassoc_frame:: mac_res_get_hmac_vap fail.vap_id:%d}",pst_mac_vap->uc_vap_id);
            oal_netbuf_free(pst_disassoc);
            return;
        }

        hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_STA_FAKE_UP);
    }

    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_disassoc);

        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC, "{hmac_mgmt_send_disassoc_frame::hmac_tx_mgmt_send_event failed[%d].}", ul_ret);
    }
}


/*****************************************************************************
 �� �� ��  : hmac_mgmt_update_assoc_user_qos_table
 ��������  : ���¶�Ӧ����ʵ���qos������Ϣ:�����Ĺ������ڹ����û�WMMʹ�ܵ������
             ��dmac���¼�д�Ĵ�������������û�֮ǰ����WMMʹ�ܵģ��򲻱��ظ�д��
             ���������֮ǰ����WMMʹ�ܵģ�����Ҳ����WMMʹ�ܵģ�����д�Ĵ���
 �������  : puc_payload :ָ��֡���ָ��
             ul_msg_len  :֡�ĳ���
             us_info_elem_offset:Ŀǰ֡��λ�õ�ƫ��
             pst_hmac_user      :ָ��hmac_user��ָ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��24��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_mgmt_update_assoc_user_qos_table(
                oal_uint8                      *puc_payload,
                oal_uint16                      us_msg_len,
                oal_uint16                      us_info_elem_offset,
                hmac_user_stru                 *pst_hmac_user)
{
    frw_event_mem_stru                       *pst_event_mem;
    frw_event_stru                           *pst_event;
    dmac_ctx_asoc_set_reg_stru                st_asoc_set_reg_param = {0};
    oal_uint8                                *puc_ie                = OAL_PTR_NULL;

    /* ��������û�֮ǰ����wmmʹ�ܵģ�ʲô����������ֱ�ӷ���  */
    if (OAL_TRUE == pst_hmac_user->st_user_base_info.st_cap_info.bit_qos)
    {
        OAM_INFO_LOG0(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ASSOC,
                      "{hmac_mgmt_update_assoc_user_qos_table::assoc user is wmm cap already.}");
        return;
    }

    mac_user_set_qos(&pst_hmac_user->st_user_base_info, OAL_FALSE);

    if (us_info_elem_offset < us_msg_len)
    {
        us_msg_len  -= us_info_elem_offset;
        puc_payload += us_info_elem_offset;

        puc_ie = mac_get_wmm_ie(puc_payload, us_msg_len);
        if (OAL_PTR_NULL != puc_ie)
        {
            mac_user_set_qos(&pst_hmac_user->st_user_base_info, OAL_TRUE);
        }
        else
        {
            /* ��������û�֮ǰ����û��Я��wmm ie, �ٲ���HT CAP���� */
            puc_ie = mac_find_ie(MAC_EID_HT_CAP, puc_payload, us_msg_len);
            if (OAL_PTR_NULL != puc_ie)
            {
                mac_user_set_qos(&pst_hmac_user->st_user_base_info, OAL_TRUE);
            }
        }
    }

    /* ��������û���������Ȼ����wmmʹ�ܵģ�ʲôҲ������ֱ�ӷ��� */
    if (OAL_FALSE == pst_hmac_user->st_user_base_info.st_cap_info.bit_qos)
    {
        OAM_INFO_LOG0(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ASSOC,
                      "{hmac_mgmt_update_assoc_user_qos_table::assoc user is not wmm cap.}");
        return;
    }

    /* �������û��Ӳ�֧��wmm��֧��wmmת��ʱ�����¼���DMAC д�Ĵ���*/

    /* �����¼��ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_ctx_asoc_set_reg_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG1(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ASSOC,
                      "{hmac_mgmt_update_assoc_user_qos_table::event_mem alloc null, size[%d].}", OAL_SIZEOF(dmac_ctx_asoc_set_reg_stru));
        return;
    }

    st_asoc_set_reg_param.uc_user_index = pst_hmac_user->st_user_base_info.us_assoc_id;

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_ASOC_WRITE_REG,
                       OAL_SIZEOF(dmac_ctx_asoc_set_reg_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_hmac_user->st_user_base_info.uc_chip_id,
                       pst_hmac_user->st_user_base_info.uc_device_id,
                       pst_hmac_user->st_user_base_info.uc_vap_id);

    /* �������� */
    oal_memcopy(pst_event->auc_event_data, (oal_void *)&st_asoc_set_reg_param, OAL_SIZEOF(dmac_ctx_asoc_set_reg_stru));

    /* �ַ��¼� */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_update_11ntxbf_cap
 ��������  : ����user��11n txbf����
 �������  : puc_payload        :ָ��vendor ie��ָ��
             pst_hmac_user      :ָ��hmac_user��ָ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��2��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_TXBF
oal_void hmac_mgmt_update_11ntxbf_cap(
                oal_uint8                      *puc_payload,
                hmac_user_stru                 *pst_hmac_user)
{
    mac_11ntxbf_vendor_ie_stru *pst_vendor_ie;
    if ((OAL_PTR_NULL == puc_payload))
    {
        return;
    }

    /* ��⵽vendor ie*/
    pst_vendor_ie = (mac_11ntxbf_vendor_ie_stru *)puc_payload;

    pst_hmac_user->st_user_base_info.st_cap_info.bit_11ntxbf = pst_vendor_ie->st_11ntxbf.bit_11ntxbf;

    return ;
}
#endif /* #ifdef _PRE_WLAN_FEATURE_TXBF */

/*****************************************************************************
 �� �� ��  : hmac_check_bss_cap_info
 ��������  : check capabilities info field ��mac��Ϣ����BSS type, Privacy���Ƿ���VAP���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��6��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_check_bss_cap_info(oal_uint16 us_cap_info,mac_vap_stru *pst_mac_vap)
{
    hmac_vap_stru                        *pst_hmac_vap;
    oal_uint32                            ul_ret = OAL_FALSE;
    wlan_mib_desired_bsstype_enum_uint8   en_bss_type;

    /* ��ȡCAP INFO��BSS TYPE */
    en_bss_type  =  mac_get_bss_type(us_cap_info);

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_check_bss_cap_info::pst_hmac_vap null.}");
        return OAL_FAIL;
    }

    /* �Ƚ�BSS TYPE�Ƿ�һ�� ��һ�£������STA��Ȼ�������������Ӽ����ԣ�����ģʽ�򷵻ز�֧�� */
    if (en_bss_type != pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11DesiredBSSType)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_check_bss_cap_info::vap_bss_type[%d] is different from asoc_user_bss_type[%d].}",
                         pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11DesiredBSSType, en_bss_type);
    }

    if (OAL_TRUE == pst_hmac_vap->en_wps_active)
    {
        return OAL_TRUE;
    }

    /* �Ƚ�CAP INFO��privacyλ������Ƿ���ܣ����ܲ�һ�£�����ʧ�� */
    ul_ret = mac_check_mac_privacy(us_cap_info,(oal_uint8 *)pst_mac_vap);
    if (ul_ret != OAL_TRUE)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_check_bss_cap_info::mac privacy capabilities is different.}");
    }

    return OAL_TRUE;
}
#if 0
/*****************************************************************************
 �� �� ��  : hmac_is_rate_support
 ��������  : �ж��û��Ƿ�֧��ĳ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  hmac_user_is_rate_support(hmac_user_stru *pst_hmac_user, oal_uint8 uc_rate)
{
    mac_rate_stru       *pst_op_rates;
    oal_bool_enum_uint8  en_rate_is_supp = OAL_FALSE;
    oal_uint8            uc_loop;

    pst_op_rates = &(pst_hmac_user->st_op_rates);

    for (uc_loop = 0; uc_loop < pst_op_rates->uc_rs_nrates; uc_loop++)
    {
        if ((pst_op_rates->auc_rs_rates[uc_loop] & 0x7F) == uc_rate)
        {
            en_rate_is_supp = OAL_TRUE;
            break;
        }
    }

    return en_rate_is_supp;
}
#endif
/*****************************************************************************
 �� �� ��  : hmac_set_user_protocol_mode
 ��������  : ��ȡ�û���Э��ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_set_user_protocol_mode(mac_vap_stru *pst_mac_vap, hmac_user_stru *pst_hmac_user)
{
    mac_user_ht_hdl_stru         *pst_mac_ht_hdl;
    mac_vht_hdl_stru             *pst_mac_vht_hdl;
    mac_user_stru                *pst_mac_user;

    /* ��ȡHT��VHT�ṹ��ָ�� */
    pst_mac_user    = &pst_hmac_user->st_user_base_info;
    pst_mac_vht_hdl = &(pst_mac_user->st_vht_hdl);
    pst_mac_ht_hdl  = &(pst_mac_user->st_ht_hdl);

    if (OAL_TRUE == pst_mac_vht_hdl->en_vht_capable)
    {
        mac_user_set_protocol_mode(pst_mac_user, WLAN_VHT_MODE);
    }
    else if (OAL_TRUE == pst_mac_ht_hdl->en_ht_capable)
    {
        mac_user_set_protocol_mode(pst_mac_user, WLAN_HT_MODE);
    }
    else
    {
        if (WLAN_BAND_5G == pst_mac_vap->st_channel.en_band)            /* �ж��Ƿ���5G */
        {
            mac_user_set_protocol_mode(pst_mac_user, WLAN_LEGACY_11A_MODE);
        }
        else
        {
            if (OAL_TRUE == hmac_is_support_11grate(pst_hmac_user->st_op_rates.auc_rs_rates, pst_hmac_user->st_op_rates.uc_rs_nrates))
            {
                mac_user_set_protocol_mode(pst_mac_user, WLAN_LEGACY_11G_MODE);
                if (OAL_TRUE == hmac_is_support_11brate(pst_hmac_user->st_op_rates.auc_rs_rates, pst_hmac_user->st_op_rates.uc_rs_nrates))
                {
                    mac_user_set_protocol_mode(pst_mac_user, WLAN_MIXED_ONE_11G_MODE);
                }
            }
            else if (OAL_TRUE == hmac_is_support_11brate(pst_hmac_user->st_op_rates.auc_rs_rates, pst_hmac_user->st_op_rates.uc_rs_nrates))
            {
                mac_user_set_protocol_mode(pst_mac_user, WLAN_LEGACY_11B_MODE);
            }
            else
            {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_set_user_protocol_mode::set user protocol failed.}");
            }
        }
    }


    /* ���������⣺˼��AP 2.4G��11b����5G(11a)����ʱ���͵�assoc rsp֡Я�������ʷֱ���11g��11b������STA�����û�ʱ֪ͨ�㷨ʧ�ܣ�
    AutorateʧЧ��DBAC����£�DBAC�޷������ѹ�����VAP״̬�޷��ָ������� ��ʱ������������ԶԶ������쳣�����ͳһ�����Ż� */
    if (((WLAN_LEGACY_11B_MODE == pst_mac_user->en_protocol_mode) && (WLAN_LEGACY_11A_MODE == pst_mac_vap->en_protocol))
        || ((WLAN_LEGACY_11G_MODE == pst_mac_user->en_protocol_mode) && (WLAN_LEGACY_11B_MODE == pst_mac_vap->en_protocol)))
    {
        mac_user_set_protocol_mode(pst_mac_user, pst_mac_vap->en_protocol);
        oal_memcopy((oal_void *)&(pst_hmac_user->st_op_rates), (oal_void *)&(pst_mac_vap->st_curr_sup_rates.st_rate), OAL_SIZEOF(mac_rate_stru));
    }
}
/*****************************************************************************
 �� �� ��  : hmac_user_init_rates
 ��������  : ��ʼ���û����ʼ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��21��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_user_init_rates(hmac_user_stru *pst_hmac_user, mac_vap_stru *pst_mac_vap)
{
    oal_uint8                       uc_rate_idx;
    mac_rate_stru                  *pst_avail_op_rates;

    oal_memset(pst_hmac_user->st_op_rates.auc_rs_rates, 0, WLAN_MAX_SUPP_RATES);
    pst_hmac_user->st_op_rates.uc_rs_nrates = 0;

    pst_avail_op_rates = &(pst_hmac_user->st_user_base_info.st_avail_op_rates);
    pst_avail_op_rates->uc_rs_nrates = pst_mac_vap->st_curr_sup_rates.st_rate.uc_rs_nrates;

    for (uc_rate_idx = 0; uc_rate_idx < pst_avail_op_rates->uc_rs_nrates; uc_rate_idx++)
    {
        pst_avail_op_rates->auc_rs_rates[uc_rate_idx] = pst_mac_vap->st_curr_sup_rates.st_rate.ast_rs_rates[uc_rate_idx].uc_mac_rate;
    }
}
/*****************************************************************************
 �� �� ��  : hmac_add_user_rates
 ��������  : �����û����ʼ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��21��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8 hmac_add_user_rates(hmac_user_stru *pst_hmac_user, oal_uint8 uc_rates_cnt, oal_uint8 *puc_rates)
{
    if (pst_hmac_user->st_op_rates.uc_rs_nrates + uc_rates_cnt > WLAN_MAX_SUPP_RATES)
    {
        uc_rates_cnt = WLAN_MAX_SUPP_RATES - pst_hmac_user->st_op_rates.uc_rs_nrates;
    }

    oal_memcopy(&(pst_hmac_user->st_op_rates.auc_rs_rates[pst_hmac_user->st_op_rates.uc_rs_nrates]), puc_rates, uc_rates_cnt);
    pst_hmac_user->st_op_rates.uc_rs_nrates += uc_rates_cnt;

    return uc_rates_cnt;
}

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)

/*****************************************************************************
 �� �� ��  : hmac_rx_sa_query_req
 ��������  : AP��UP״̬�µĽ���SA Query request֡����
 �������  : pst_hmac_vap: HMAC VAPָ��
             pst_netbuf  : ����֡���ڵ�sk_buff
             en_is_protected �˹���֡�Ƿ��ܵ�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��09��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_rx_sa_query_req(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf, oal_bool_enum_uint8 en_is_protected)
{
    oal_uint8                   *puc_sa;
    hmac_user_stru              *pst_hmac_user   = OAL_PTR_NULL;
    oal_uint8                   *puc_mac_hdr     = OAL_PTR_NULL;

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_netbuf))
    {
        OAM_ERROR_LOG2(0, OAM_SF_RX, "{hmac_rx_sa_query_req::null param %d %d.}", pst_hmac_vap, pst_netbuf);
        return;
    }

    puc_mac_hdr  = OAL_NETBUF_HEADER(pst_netbuf);

    mac_rx_get_sa((mac_ieee80211_frame_stru *)puc_mac_hdr, &puc_sa);
    pst_hmac_user = mac_vap_get_hmac_user_by_addr(&pst_hmac_vap->st_vap_base_info, puc_sa);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                      "{hmac_rx_sa_query_req::pst_hmac_user null.}");
        return;
    }

    /*������û��Ĺ���֡�������Բ�һ�£������ñ���*/
    if (en_is_protected != pst_hmac_user->st_user_base_info.st_cap_info.bit_pmf_active)
    {
       OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                      "{hmac_rx_sa_query_req::PMF check failed.}");
       return;
    }

    /*sa Query rsp����*/
    hmac_send_sa_query_rsp(&pst_hmac_vap->st_vap_base_info, puc_mac_hdr, en_is_protected);

    return;

}
 /*****************************************************************************
     �� �� ��  : hmac_rx_sa_query_rsp
     ��������  : UP״̬�µĽ���SA Query rsponse֡����
     �������  : pst_hmac_vap   : HMAC VAPָ��
                 pst_netbuf     : ����֡���ڵ�sk_buff
                 en_is_protected: ��������֡���ܵı�־λ
     �������  : ��
     �� �� ֵ  : ��
     ���ú���  :
     ��������  :

     �޸���ʷ      :
        1.��    ��   : 2014��4��09��
          ��    ��   : z00273164
          �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_rx_sa_query_rsp(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf, oal_bool_enum_uint8 en_is_protected)
{
     oal_uint8                   *puc_mac_hdr     = OAL_PTR_NULL;
     oal_uint8                   *puc_sa;
     hmac_user_stru              *pst_hmac_user   = OAL_PTR_NULL;
     oal_uint16                  *pus_trans_id;
     mac_sa_query_stru           *pst_sa_query_info;

     if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_netbuf))
     {
         OAM_ERROR_LOG2(0, OAM_SF_AMPDU, "{hmac_rx_sa_query_rsp::param null,%d %d.}", pst_hmac_vap, pst_netbuf);
         return ;
     }

     puc_mac_hdr  = OAL_NETBUF_HEADER(pst_netbuf);

     mac_rx_get_sa((mac_ieee80211_frame_stru *)puc_mac_hdr, &puc_sa);
     pst_hmac_user = mac_vap_get_hmac_user_by_addr(&pst_hmac_vap->st_vap_base_info, puc_sa);
     if (OAL_PTR_NULL == pst_hmac_user)
     {
         OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "{hmac_rx_sa_query_rsp::pst_hmac_user null.}");
         return ;
     }

     /*������û��Ĺ���֡�������Բ�һ�£������ñ���*/
     if (en_is_protected != pst_hmac_user->st_user_base_info.st_cap_info.bit_pmf_active)
     {
         OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "{hmac_rx_sa_query_rsp::PMF check failed.}");
         return ;
     }

     /*�Ա�trans_id*/
     pus_trans_id = (oal_uint16 *)(puc_mac_hdr + MAC_80211_FRAME_LEN + 2);
     pst_sa_query_info = &pst_hmac_user->st_sa_query_info;

     /*�յ���Ч��SA query reqponse������������Ч��SA*/
     if (0 == oal_memcmp(pus_trans_id, &(pst_sa_query_info->us_sa_query_trans_id), 2))
     {
         /* pending SA Query requests ���������� & sa query���̿�ʼʱ������*/
         pst_sa_query_info->ul_sa_query_count      = 0;
         pst_sa_query_info->ul_sa_query_start_time = 0;

         /* ɾ��timer */
         if (OAL_FALSE != pst_sa_query_info->st_sa_query_interval_timer.en_is_registerd)
         {
             FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_sa_query_info->st_sa_query_interval_timer));
         }

         /* ɾ��timers����δ洢�ռ� */
         if (OAL_PTR_NULL != pst_sa_query_info->st_sa_query_interval_timer.p_timeout_arg)
         {
            OAL_MEM_FREE((oal_void *)pst_sa_query_info->st_sa_query_interval_timer.p_timeout_arg, OAL_TRUE);
            pst_sa_query_info->st_sa_query_interval_timer.p_timeout_arg = OAL_PTR_NULL;
         }

     }

     return ;

}
#endif
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
/*****************************************************************************
 �� �� ��  : hmac_rx_opmode_notify_frame
 ��������  : �ӿտڽ���opmode_notify֡�Ĵ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��10��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_mgmt_rx_opmode_notify_frame(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf)
{
    mac_opmode_notify_stru     *pst_opmode_notify = OAL_PTR_NULL;
    oal_uint8                   uc_mgmt_frm_type;
    oal_uint8                  *puc_frame_payload;
    mac_ieee80211_frame_stru   *pst_mac_header;
    frw_event_mem_stru         *pst_event_mem;
    frw_event_stru             *pst_event;
    oal_uint8                   uc_power_save;
    oal_uint16                 *pus_user_id;
    mac_user_stru              *pst_mac_user;
    dmac_rx_ctl_stru           *pst_rx_ctrl;
    oal_uint16                  us_user_idx = 0;
    oal_uint8                   auc_sta_addr[WLAN_MAC_ADDR_LEN];
    oal_uint8                  *puc_data;
    oal_uint32                  ul_ret;

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_netbuf))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{hmac_mgmt_rx_opmode_notify_frame::pst_hmac_vap = [%x], pst_netbuf = [%x]!}\r\n",
                        pst_hmac_vap, pst_netbuf);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if ((OAL_FALSE == mac_mib_get_VHTOptionImplemented(&pst_hmac_vap->st_vap_base_info))
        || (OAL_FALSE == mac_mib_get_OperatingModeNotificationImplemented(&pst_hmac_vap->st_vap_base_info)))
    {
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_mgmt_rx_opmode_notify_frame::the vap is not support OperatingModeNotification!}\r\n");
        return OAL_SUCC;
    }


    pst_rx_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    mac_get_address2((oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr, auc_sta_addr);

    ul_ret = mac_vap_find_user_by_macaddr(&(pst_hmac_vap->st_vap_base_info), auc_sta_addr, &us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SMPS,
                      "{hmac_mgmt_rx_opmode_notify_frame::mac_vap_find_user_by_macaddr failed[%d].}", ul_ret);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SMPS, "{hmac_mgmt_rx_opmode_notify_frame::pst_mac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ֡��ָ�� */
    puc_data = (oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr;

    uc_mgmt_frm_type  = mac_get_frame_sub_type(puc_data);

    /* �Ƿ���Ҫ����Power Management bitλ */
    pst_mac_header = (mac_ieee80211_frame_stru *)puc_data;
    uc_power_save = (oal_uint8)pst_mac_header->st_frame_control.bit_power_mgmt;

    /* �������λ����(bit_power_mgmt == 1),���¼���DMAC�������û�������Ϣ */
    if ((OAL_TRUE == uc_power_save) && (WLAN_VAP_MODE_BSS_AP == pst_hmac_vap->st_vap_base_info.en_vap_mode))
    {
        /* �����¼��ڴ� */
        pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(oal_uint16));
        if (OAL_PTR_NULL == pst_event_mem)
        {
            OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_mgmt_rx_opmode_notify_frame::FRW_EVENT_ALLOC fail!}\r\n");
            return OAL_FAIL;
        }

        /* ��д�¼� */
        pst_event = (frw_event_stru *)pst_event_mem->puc_data;

        FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                           FRW_EVENT_TYPE_WLAN_CTX,
                           DMAC_WLAN_CTX_EVENT_SUB_TYPE_PSM_OPMODE_NOTIFY,
                           OAL_SIZEOF(oal_uint16),
                           FRW_EVENT_PIPELINE_STAGE_1,
                           pst_mac_user->uc_chip_id,
                           pst_mac_user->uc_device_id,
                           pst_mac_user->uc_vap_id);

        pus_user_id = (oal_uint16 *)pst_event->auc_event_data;

        *pus_user_id = us_user_idx;

        /* �ַ��¼� */
        frw_event_dispatch_event(pst_event_mem);
        FRW_EVENT_FREE(pst_event_mem);
    }

    /****************************************************/
    /*   OperatingModeNotification Frame - Frame Body   */
    /* -------------------------------------------------*/
    /* |   Category   |   Action   |   OperatingMode   |*/
    /* -------------------------------------------------*/
    /* |   1          |   1        |   1               |*/
    /* -------------------------------------------------*/
    /*                                                  */
    /****************************************************/

    /* ��ȡpayload��ָ�� */
    puc_frame_payload = (oal_uint8 *)puc_data + MAC_80211_FRAME_LEN;
    pst_opmode_notify = (mac_opmode_notify_stru *)(puc_frame_payload + MAC_ACTION_OFFSET_ACTION + 1);

    ul_ret = mac_ie_proc_opmode_field(&(pst_hmac_vap->st_vap_base_info), pst_mac_user, pst_opmode_notify);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_mac_user->uc_vap_id, OAM_SF_CFG, "{hmac_mgmt_rx_opmode_notify_frame::hmac_config_send_event failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* opmodeϢͬ��dmac */
    ul_ret = hmac_config_update_opmode_event(&(pst_hmac_vap->st_vap_base_info), pst_mac_user, uc_mgmt_frm_type);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_mac_user->uc_vap_id, OAM_SF_CFG, "{hmac_mgmt_rx_opmode_notify_frame::hmac_config_send_event failed[%d].}", ul_ret);
    }
    return ul_ret;
}
#endif

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
/*****************************************************************************
 �� �� ��  : hmac_rx_notify_channel_width
 ��������  : AP��UP״̬�´���"Notify Channel Width"֡
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
             pst_netbuf  : "Notify Channel Width֡"���ڵ�netbuf
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��27��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��7��18��
    ��    ��   : zhangyu
    �޸�����   : AP����STA�ຯ���ع�

*****************************************************************************/
oal_void  hmac_rx_notify_channel_width(mac_vap_stru *pst_mac_vap, oal_netbuf_stru *pst_netbuf)
{
    hmac_user_stru        *pst_hmac_user;
    dmac_rx_ctl_stru      *pst_rx_ctrl;
    oal_uint8              auc_sta_addr[WLAN_MAC_ADDR_LEN];
    oal_uint8             *puc_data;
    oal_uint32             ul_ret;

    if (OAL_FALSE == mac_mib_get_HighThroughputOptionImplemented(pst_mac_vap))
    {
        return;
    }

    pst_rx_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    /* ��ȡ���Ͷ˵�ַ */
    mac_get_address2((oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr, auc_sta_addr);

    /* ���ݷ��Ͷ˵��ҵ���ӦAP USER�ṹ */
    pst_hmac_user = mac_vap_get_hmac_user_by_addr(pst_mac_vap, auc_sta_addr);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_rx_notify_channel_width::pst_hmac_user null.}");
        return;
    }

    /* ��ȡ֡��ָ�� */
    puc_data = (oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr + pst_rx_ctrl->st_rx_info.uc_mac_header_len;

    /* ���µ�"STA Channel Width" field */
    mac_ie_proc_chwidth_field(pst_mac_vap, &(pst_hmac_user->st_user_base_info),(puc_data[MAC_ACTION_OFFSET_ACTION + 1] & BIT0));

    /* �����û�֧�ִ���������Э�̳���ǰ����dmac offload�ܹ��£�ͬ��������Ϣ��device */
    ul_ret = hmac_config_user_info_syn(pst_mac_vap, &(pst_hmac_user->st_user_base_info));
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                "{hmac_rx_notify_channel_width::usr_info_syn failed[%d].}", ul_ret);
    }

}

#endif

/*****************************************************************************
 �� �� ��  : hmac_send_mgmt_to_host
 ��������  : �ϱ����յ��Ĺ���֡
 �������  : hmac_vap_stru  *pst_hmac_vap,
             oal_uint8      *puc_buf,
             oal_uint16      us_len,
             oal_int         l_freq
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��17��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_send_mgmt_to_host(hmac_vap_stru  *pst_hmac_vap,
                                                oal_netbuf_stru *puc_buf,
                                                oal_uint16       us_len,
                                                oal_int          l_freq)
{
    mac_device_stru         *pst_mac_device;
    frw_event_mem_stru      *pst_event_mem;
    frw_event_stru          *pst_event;
    hmac_rx_mgmt_event_stru *pst_mgmt_frame;
    mac_rx_ctl_stru            *pst_rx_info;
#ifdef _PRE_WLAN_FEATURE_P2P
    mac_ieee80211_frame_stru   *pst_frame_hdr;
    mac_vap_stru            *pst_mac_vap;
    oal_uint8                uc_hal_vap_id;
#endif
#ifdef _PRE_WLAN_FEATURE_HILINK
    dmac_rx_ctl_stru        *pst_rx_ctrl;
#endif
    oal_uint8*               pst_mgmt_data;

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_send_mgmt_to_host::pst_mac_device null.}");
        return;
    }

    /* �׹���һ���µ�sta����¼���WAL */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(hmac_rx_mgmt_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_send_mgmt_to_host::pst_event_mem null.}");
        return;
    }

#ifdef _PRE_WLAN_FEATURE_HILINK
    pst_rx_ctrl     = (dmac_rx_ctl_stru *)oal_netbuf_cb(puc_buf);
#endif
    pst_rx_info     = (mac_rx_ctl_stru *)oal_netbuf_cb(puc_buf);


    pst_mgmt_data = (oal_uint8*)oal_memalloc(us_len);
    if(OAL_PTR_NULL == pst_mgmt_data)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_send_mgmt_to_host::pst_mgmt_data null.}");
        return;
    }
    oal_memcopy(pst_mgmt_data, (oal_uint8 *)pst_rx_info->pul_mac_hdr_start_addr, us_len);

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_CTX,
                       HMAC_HOST_CTX_EVENT_SUB_TYPE_RX_MGMT,
                       OAL_SIZEOF(hmac_rx_mgmt_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_0,
                       pst_hmac_vap->st_vap_base_info.uc_chip_id,
                       pst_hmac_vap->st_vap_base_info.uc_device_id,
                       pst_hmac_vap->st_vap_base_info.uc_vap_id);

    /* ��д�ϱ�����֡���� */
    pst_mgmt_frame = (hmac_rx_mgmt_event_stru *)(pst_event->auc_event_data);
    pst_mgmt_frame->puc_buf = (oal_uint8 *)pst_mgmt_data;
    pst_mgmt_frame->us_len  = us_len;
    pst_mgmt_frame->l_freq  = l_freq;
#ifdef _PRE_WLAN_FEATURE_HILINK
    pst_mgmt_frame->uc_rssi = pst_rx_ctrl->st_rx_statistic.c_rssi_dbm + HMAC_FBT_RSSI_ADJUST_VALUE;
#endif
    OAL_NETBUF_LEN(puc_buf) = us_len;

    oal_memcopy(pst_mgmt_frame->ac_name, pst_hmac_vap->pst_net_device->name, OAL_IF_NAME_SIZE);
#ifdef _PRE_WLAN_FEATURE_P2P
    pst_frame_hdr  = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(pst_rx_info);
    pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);
    if (!IS_LEGACY_VAP(pst_mac_vap))
    {
        /* �����P2P�豸������P2P vap ����һ��vap ��Ӧ���hal_vap �������P2P vap ������һ��vap ��Ӧ���hal_vap ��� */
        /* �ԱȽ��յ��Ĺ���֡vap_id �Ƿ��vap ��hal_vap_id ��ͬ */

        /* �ӹ���֡cb�ֶ��е�hal vap id ����Ӧ��Ϣ���Ҷ�Ӧ��net dev ָ��*/
        uc_hal_vap_id = MAC_GET_RX_CB_HAL_VAP_IDX((mac_rx_ctl_stru *)oal_netbuf_cb(puc_buf));
        if (0 == oal_compare_mac_addr(pst_frame_hdr->auc_address1, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID))
        //if (pst_hmac_vap->st_vap_base_info.uc_p2p0_hal_vap_id == uc_hal_vap_id)
        {
            /*�ڶ���net dev��*/
            oal_memcopy(pst_mgmt_frame->ac_name, pst_hmac_vap->pst_p2p0_net_device->name, OAL_IF_NAME_SIZE);
        }
        else if (0 == oal_compare_mac_addr(pst_frame_hdr->auc_address1, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID))
        //else if (pst_hmac_vap->st_vap_base_info.uc_p2p_gocl_hal_vap_id == uc_hal_vap_id)
        {
            oal_memcopy(pst_mgmt_frame->ac_name, pst_hmac_vap->pst_net_device->name, OAL_IF_NAME_SIZE);
        }
        else if((14 == uc_hal_vap_id)&&
                (WLAN_PROBE_REQ == pst_frame_hdr->st_frame_control.bit_sub_type)&&
                (IS_P2P_CL(pst_mac_vap)||IS_P2P_DEV(pst_mac_vap)))
        {
#if 0
            //probe requestĿǰ���ϱ�wpa supplicant
            //oal_memcopy(pst_mgmt_frame->ac_name, pst_hmac_vap->pst_p2p0_net_device->name, OAL_IF_NAME_SIZE);
#endif
            FRW_EVENT_FREE(pst_event_mem);
            oal_free(pst_mgmt_data);
            return;
        }
        else
        {
            //OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P,
            //                "{hmac_send_mgmt_to_host::error!.uc_hal_vap_id %d}", uc_hal_vap_id);
            FRW_EVENT_FREE(pst_event_mem);
            oal_free(pst_mgmt_data);

            return;
        }
    }
#endif

    /* �ַ��¼� */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

}

/*****************************************************************************
 �� �� ��  : hmac_wpas_mgmt_tx
 ��������  : ����wpa_supplicant action frame
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��25��
    ��    ��   : xiaoyuren
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_wpas_mgmt_tx(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_netbuf_stru                *pst_netbuf_mgmt_tx    =OAL_PTR_NULL;
    mac_tx_ctl_stru                *pst_tx_ctl;
    oal_uint32                      ul_ret;
    mac_mgmt_frame_stru            *pst_mgmt_tx;
   // mac_cfg_add_user_param_stru     st_add_user;//TBD:P2P DKY BUG ,���͵���֡��Ҫ������û�
   // oal_uint8                      *puc_da;
    //oal_uint16                      us_user_idx;
    mac_device_stru                *pst_mac_device;

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_P2P, "{hmac_wpas_mgmt_tx::param null, %d %d.}", pst_mac_vap, pst_mac_vap);
        return OAL_FAIL;
    }

    pst_mgmt_tx = (mac_mgmt_frame_stru *)puc_param;

    pst_mac_device  = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_P2P, "{hmac_wpas_mgmt_tx::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_P2P, "{hmac_wpas_mgmt_tx::mgmt frame id=[%d]}", pst_mgmt_tx->mgmt_frame_id);

    /*  ����netbuf �ռ�*/
    pst_netbuf_mgmt_tx = (oal_netbuf_stru *)OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, pst_mgmt_tx->us_len, OAL_NETBUF_PRIORITY_MID);

    if(OAL_PTR_NULL == pst_netbuf_mgmt_tx)
    {
        /* Reserved Memory pool tried for high priority deauth frames */
        pst_netbuf_mgmt_tx = (oal_netbuf_stru *)OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF,WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
        if(OAL_PTR_NULL == pst_netbuf_mgmt_tx)
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_P2P, "{hmac_wpas_mgmt_tx::pst_mgmt_tx null.}");
            return OAL_FAIL;
        }
    }
    OAL_MEM_NETBUF_TRACE(pst_netbuf_mgmt_tx, OAL_TRUE);

    OAL_MEMZERO(oal_netbuf_cb(pst_netbuf_mgmt_tx), OAL_SIZEOF(mac_tx_ctl_stru));

    /*���netbuf*/
    oal_memcopy( (oal_uint8 *)OAL_NETBUF_HEADER(pst_netbuf_mgmt_tx), pst_mgmt_tx->puc_frame, pst_mgmt_tx->us_len);
    oal_netbuf_put(pst_netbuf_mgmt_tx, pst_mgmt_tx->us_len);

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf_mgmt_tx);                              /* ��ȡcb�ṹ�� */
    pst_tx_ctl->us_mpdu_len       = pst_mgmt_tx->us_len;                                      /* dmac������Ҫ��mpdu���� */
    //pst_tx_ctl->us_tx_user_idx    = st_add_user.us_user_idx;  /* ���������Ҫ��ȡuser�ṹ�� */
    pst_tx_ctl->us_tx_user_idx    = 0xF;                       /* ���������Ҫ��ȡuser�ṹ�� */
    pst_tx_ctl->bit_need_rsp      = OAL_TRUE;
    pst_tx_ctl->bit_is_vipframe   = OAL_TRUE;
    pst_tx_ctl->bit_is_needretry  = OAL_TRUE;
    pst_tx_ctl->bit_mgmt_frame_id = pst_mgmt_tx->mgmt_frame_id;


    /* Buffer this frame in the Memory Queue for transmission */
    ul_ret = hmac_tx_mgmt_send_event(pst_mac_vap, pst_netbuf_mgmt_tx, pst_mgmt_tx->us_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_netbuf_mgmt_tx);

        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_P2P, "{hmac_wpas_mgmt_tx::hmac_tx_mgmt_send_event failed[%d].}", ul_ret);
        return OAL_FAIL;
    }

    return OAL_SUCC;
}

#if defined(_PRE_WLAN_FEATURE_HS20) || defined(_PRE_WLAN_FEATURE_P2P) || defined(_PRE_WLAN_FEATURE_HILINK)

/*****************************************************************************
 �� �� ��  : hmac_rx_mgmt_send_to_host
 ��������  : ���յ�����֡���ϱ�host
 �������  : hmac_vap_stru *pst_hmac_vap
             oal_netbuf_stru *pst_netbuf
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��25��
    ��    ��   : w00346925
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_rx_mgmt_send_to_host(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf)
{
    mac_rx_ctl_stru            *pst_rx_info;
    oal_int                     l_freq = 0;

    pst_rx_info  = (mac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    l_freq = oal_ieee80211_channel_to_frequency(pst_rx_info->uc_channel_number,
                                                (pst_rx_info->uc_channel_number > 14) ? IEEE80211_BAND_5GHZ : IEEE80211_BAND_2GHZ);
    hmac_send_mgmt_to_host(pst_hmac_vap, pst_netbuf, pst_rx_info->us_frame_len, l_freq);
}
#endif

/*****************************************************************************
 �� �� ��  : hmac_mgmt_tx_event_status
 ��������  : ����dmac�ϱ�����֡���͵Ľ��,�ϱ�WAL
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��31��
    ��    ��   : xiaoyuren
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_mgmt_tx_event_status(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_crx_mgmt_tx_status_stru    *pst_mgmt_tx_status_param;
    dmac_crx_mgmt_tx_status_stru    *pst_mgmt_tx_status_param_2wal;
    frw_event_mem_stru              *pst_event_mem;
    frw_event_stru                  *pst_event;
    //mac_cfg_del_user_param_stru      st_del_user;
    oal_uint32                       ul_ret;
    //hmac_user_stru                  *pst_hmac_user;
    //mac_device_stru                 *pst_mac_device;
    //oal_uint8                        auc_user_mac_adr[WLAN_MAC_ADDR_LEN] = {0};

    if (OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG0(0, OAM_SF_P2P, "{hmac_mgmt_tx_event_status::puc_param is null!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mgmt_tx_status_param = (dmac_crx_mgmt_tx_status_stru *)puc_param;

    OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_P2P, "{hmac_mgmt_tx_event_status::dmac tx mgmt status report.userindx[%d], tx mgmt status[%d], frame_id[%d]}",
                           pst_mgmt_tx_status_param->uc_user_idx,
                           pst_mgmt_tx_status_param->uc_dscr_status,
                           pst_mgmt_tx_status_param->mgmt_frame_id);

    /* ��ɨ������¼���WAL*/
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_crx_mgmt_tx_status_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_P2P, "{hmac_mgmt_tx_event_status::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_CTX,
                       HMAC_HOST_CTX_EVENT_SUB_TYPE_MGMT_TX_STATUS,
                       OAL_SIZEOF(dmac_crx_mgmt_tx_status_stru),
                       FRW_EVENT_PIPELINE_STAGE_0,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    pst_mgmt_tx_status_param_2wal = (dmac_crx_mgmt_tx_status_stru *)(pst_event->auc_event_data);
    pst_mgmt_tx_status_param_2wal->uc_dscr_status = pst_mgmt_tx_status_param->uc_dscr_status;
    pst_mgmt_tx_status_param_2wal->mgmt_frame_id  = pst_mgmt_tx_status_param->mgmt_frame_id;

    /* �ַ��¼� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);


    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : hmac_vap_set_user_avail_rates
 ��������  : ��ȡ�û���VAP���õ�11a/b/g��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_vap_set_user_avail_rates(mac_vap_stru *pst_mac_vap, hmac_user_stru *pst_hmac_user)
{
    mac_user_stru         *pst_mac_user;
    mac_curr_rateset_stru *pst_mac_vap_rate;
    mac_rate_stru         *pst_mac_user_rate;
    mac_rate_stru          st_avail_op_rates;
    oal_uint8              uc_mac_vap_rate_num;
    oal_uint8              uc_mac_user_rate_num;
    oal_uint8              uc_vap_rate_idx;
    oal_uint8              uc_user_rate_idx;
    oal_uint8              uc_user_avail_rate_idx = 0;

    /* ��ȡVAP��USER���ʵĽṹ��ָ�� */
    pst_mac_user        = &(pst_hmac_user->st_user_base_info);
    pst_mac_vap_rate    = &(pst_mac_vap->st_curr_sup_rates);
    pst_mac_user_rate   = &(pst_hmac_user->st_op_rates);
    OAL_MEMZERO((oal_uint8 *)(&st_avail_op_rates), OAL_SIZEOF(mac_rate_stru));

    uc_mac_vap_rate_num     = pst_mac_vap_rate->st_rate.uc_rs_nrates;
    uc_mac_user_rate_num    = pst_mac_user_rate->uc_rs_nrates;

    for (uc_vap_rate_idx = 0; uc_vap_rate_idx < uc_mac_vap_rate_num; uc_vap_rate_idx++)
    {
        for(uc_user_rate_idx = 0; uc_user_rate_idx < uc_mac_user_rate_num; uc_user_rate_idx++)
        {
            if ((pst_mac_vap_rate->st_rate.ast_rs_rates[uc_vap_rate_idx].uc_mac_rate > 0) && ((pst_mac_vap_rate->st_rate.ast_rs_rates[uc_vap_rate_idx].uc_mac_rate & 0x7F) == (pst_mac_user_rate->auc_rs_rates[uc_user_rate_idx] & 0x7F)))
            {
                st_avail_op_rates.auc_rs_rates[uc_user_avail_rate_idx] = (pst_mac_user_rate->auc_rs_rates[uc_user_rate_idx] & 0x7F);
                uc_user_avail_rate_idx++;
                st_avail_op_rates.uc_rs_nrates++;

            }
        }
    }

    mac_user_set_avail_op_rates(pst_mac_user, st_avail_op_rates.uc_rs_nrates, st_avail_op_rates.auc_rs_rates);
    if (0 == st_avail_op_rates.uc_rs_nrates)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_vap_set_user_avail_rates::uc_avail_op_rates_num=0.}");
    }
}
/*****************************************************************************
 �� �� ��  : hmac_proc_ht_cap_ie
 ��������  : ����ht_cap_ie����������Ӧ��vap��user����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��8��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_proc_ht_cap_ie(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, oal_uint8 *puc_ht_cap_ie)
{
    oal_uint8                           uc_mcs_bmp_index;
    oal_uint16                          us_offset;
    mac_user_ht_hdl_stru               *pst_ht_hdl;
    oal_uint16                          us_tmp_info_elem;
    oal_uint16                          us_tmp_txbf_low;
    oal_uint16                          us_ht_cap_info;
    oal_uint32                          ul_tmp_txbf_elem;

    if ((OAL_PTR_NULL == pst_mac_vap) ||
        (OAL_PTR_NULL == pst_mac_user) ||
        (OAL_PTR_NULL == puc_ht_cap_ie))
    {
        OAM_WARNING_LOG3(0, OAM_SF_ROAM,
                        "{hmac_proc_ht_cap_ie::PARAM NULL! vap=[0x%X],user=[0x%X],cap_ie=[0x%X].}", pst_mac_vap, pst_mac_user, puc_ht_cap_ie);
        return OAL_ERR_CODE_PTR_NULL;
    }

     /* ����֧��11n�Ž��к����Ĵ��� */
    if (OAL_FALSE == mac_mib_get_HighThroughputOptionImplemented(pst_mac_vap))
    {
        return OAL_SUCC;
    }

    mac_user_set_ht_capable(pst_mac_user, OAL_TRUE);

    us_offset       = 0;
    pst_ht_hdl      = &pst_mac_user->st_ht_hdl;

    /* ���� HT Capability Element �� AP����ʾ������HT capable. */
    pst_ht_hdl->en_ht_capable = OAL_TRUE;

    us_offset += MAC_IE_HDR_LEN;

    /********************************************/
    /*     ���� HT Capabilities Info Field      */
    /********************************************/
    us_ht_cap_info = OAL_MAKE_WORD16(puc_ht_cap_ie[us_offset], puc_ht_cap_ie[us_offset + 1]);

    /* ���STA��֧�ֵ�LDPC�������� B0��0:��֧�֣�1:֧�� */
    pst_ht_hdl->bit_ldpc_coding_cap = (us_ht_cap_info & BIT0);

    /* ��ȡAP��֧�ֵĴ�������  */
    pst_ht_hdl->bit_supported_channel_width = ((us_ht_cap_info & BIT1) >> 1);

    /* ���ռ临�ý���ģʽ B2~B3 */
    mac_ie_proc_sm_power_save_field(pst_mac_user, (oal_uint8)(us_ht_cap_info & (BIT2 | BIT3)));

    /* ��ȡAP֧��Greenfield��� */
    pst_ht_hdl->bit_ht_green_field = ((us_ht_cap_info & BIT4) >> 4);

    /* ��ȡAP֧��20MHz Short-GI��� */
    pst_ht_hdl->bit_short_gi_20mhz = ((us_ht_cap_info & BIT5) >> 5);

    /* ��ȡAP֧��40MHz Short-GI��� */
    pst_ht_hdl->bit_short_gi_40mhz = ((us_ht_cap_info & BIT6) >> 6);

    /* ��ȡAP֧��STBC PPDU��� */
    pst_ht_hdl->bit_rx_stbc = (oal_uint8)((us_ht_cap_info & 0x30) >> 4);

    /* ��ȡAP֧�����A-MSDU������� */
// *pus_amsdu_maxsize = (0 == (us_ht_cap_info & BIT11)) ? WLAN_MIB_MAX_AMSDU_LENGTH_SHORT : WLAN_MIB_MAX_AMSDU_LENGTH_LONG;

    /* ��ȡAP 40M��DSSS/CCK��֧����� */
    pst_ht_hdl->bit_dsss_cck_mode_40mhz = ((us_ht_cap_info & BIT12) >> 12);

    /* ��ȡAP L-SIG TXOP ������֧����� */
    pst_ht_hdl->bit_lsig_txop_protection = ((us_ht_cap_info & BIT15) >> 15);

    us_offset += MAC_HT_CAPINFO_LEN;

    /********************************************/
    /*     ���� A-MPDU Parameters Field         */
    /********************************************/

    /* ��ȡ Maximum Rx A-MPDU factor (B1 - B0) */
    pst_ht_hdl->uc_max_rx_ampdu_factor = (puc_ht_cap_ie[us_offset] & 0x03);

    /* ��ȡ Minmum Rx A-MPDU factor (B3 - B2) */
    pst_ht_hdl->uc_min_mpdu_start_spacing = (puc_ht_cap_ie[us_offset] >> 2) & 0x07;

    us_offset += MAC_HT_AMPDU_PARAMS_LEN;

    /********************************************/
    /*     ���� Supported MCS Set Field         */
    /********************************************/
    for(uc_mcs_bmp_index = 0; uc_mcs_bmp_index < WLAN_HT_MCS_BITMASK_LEN; uc_mcs_bmp_index++)
    {
        pst_ht_hdl->uc_rx_mcs_bitmask[uc_mcs_bmp_index] =
        (pst_mac_vap->pst_mib_info->st_supported_mcstx.auc_dot11SupportedMCSTxValue[uc_mcs_bmp_index])&
        (*(oal_uint8 *)(puc_ht_cap_ie + us_offset + uc_mcs_bmp_index));
    }

    pst_ht_hdl->uc_rx_mcs_bitmask[WLAN_HT_MCS_BITMASK_LEN - 1] &= 0x1F;

    us_offset += MAC_HT_SUP_MCS_SET_LEN;

    /********************************************/
    /* ���� HT Extended Capabilities Info Field */
    /********************************************/
    us_ht_cap_info = OAL_MAKE_WORD16(puc_ht_cap_ie[us_offset], puc_ht_cap_ie[us_offset + 1]);

    /* ��ȡ HTC support Information */
    pst_ht_hdl->uc_htc_support = ((us_ht_cap_info & BIT10) >> 10);

    us_offset += MAC_HT_EXT_CAP_LEN;

    /********************************************/
    /*  ���� Tx Beamforming Field               */
    /********************************************/
    us_tmp_info_elem = OAL_MAKE_WORD16(puc_ht_cap_ie[us_offset], puc_ht_cap_ie[us_offset + 1]);
    us_tmp_txbf_low  = OAL_MAKE_WORD16(puc_ht_cap_ie[us_offset + 2], puc_ht_cap_ie[us_offset + 3]);
    ul_tmp_txbf_elem = OAL_MAKE_WORD32(us_tmp_info_elem, us_tmp_txbf_low);
    pst_ht_hdl->bit_imbf_receive_cap                = (ul_tmp_txbf_elem & BIT0);
    pst_ht_hdl->bit_receive_staggered_sounding_cap  = ((ul_tmp_txbf_elem & BIT1) >> 1);
    pst_ht_hdl->bit_transmit_staggered_sounding_cap = ((ul_tmp_txbf_elem & BIT2) >> 2);
    pst_ht_hdl->bit_receive_ndp_cap                 = ((ul_tmp_txbf_elem & BIT3) >> 3);
    pst_ht_hdl->bit_transmit_ndp_cap                = ((ul_tmp_txbf_elem & BIT4) >> 4);
    pst_ht_hdl->bit_imbf_cap                        = ((ul_tmp_txbf_elem & BIT5) >> 5);
    pst_ht_hdl->bit_calibration                     = ((ul_tmp_txbf_elem & 0x000000C0) >> 6);
    pst_ht_hdl->bit_exp_csi_txbf_cap                = ((ul_tmp_txbf_elem & BIT8) >> 8);
    pst_ht_hdl->bit_exp_noncomp_txbf_cap            = ((ul_tmp_txbf_elem & BIT9) >> 9);
    pst_ht_hdl->bit_exp_comp_txbf_cap               = ((ul_tmp_txbf_elem & BIT10) >> 10);
    pst_ht_hdl->bit_exp_csi_feedback                = ((ul_tmp_txbf_elem & 0x00001800) >> 11);
    pst_ht_hdl->bit_exp_noncomp_feedback            = ((ul_tmp_txbf_elem & 0x00006000) >> 13);
    pst_ht_hdl->bit_exp_comp_feedback               = ((ul_tmp_txbf_elem & 0x0001C000) >> 15);
    pst_ht_hdl->bit_min_grouping                    = ((ul_tmp_txbf_elem & 0x00060000) >> 17);
    pst_ht_hdl->bit_csi_bfer_ant_number             = ((ul_tmp_txbf_elem & 0x001C0000) >> 19);
    pst_ht_hdl->bit_noncomp_bfer_ant_number         = ((ul_tmp_txbf_elem & 0x00600000) >> 21);
    pst_ht_hdl->bit_comp_bfer_ant_number            = ((ul_tmp_txbf_elem & 0x01C00000) >> 23);
    pst_ht_hdl->bit_csi_bfee_max_rows               = ((ul_tmp_txbf_elem & 0x06000000) >> 25);
    pst_ht_hdl->bit_channel_est_cap                 = ((ul_tmp_txbf_elem & 0x18000000) >> 27);


    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_proc_vht_cap_ie
 ��������  : ������11ac capabilities IE��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��8��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_proc_vht_cap_ie(mac_vap_stru *pst_mac_vap, hmac_user_stru *pst_hmac_user, oal_uint8 *puc_vht_cap_ie)
{
    mac_vht_hdl_stru   *pst_mac_vht_hdl;
    mac_vht_hdl_stru    st_mac_vht_hdl;
    mac_user_stru      *pst_mac_user;
    oal_uint16          us_vht_cap_filed_low;
    oal_uint16          us_vht_cap_filed_high;
    oal_uint32          ul_vht_cap_field;
    oal_uint16          us_rx_mcs_map;
    oal_uint16          us_tx_mcs_map;
    oal_uint16          us_rx_highest_supp_logGi_data;
    oal_uint16          us_tx_highest_supp_logGi_data;
    oal_uint16          us_msg_idx = 0;

    /* ����vht cap IE */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_hmac_user) || (OAL_PTR_NULL == puc_vht_cap_ie))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY, "{hmac_proc_vht_cap_ie::param null,mac_vap[0x%x], hmac_user[0x%x], vht_cap_ie[0x%x].}", pst_mac_vap, pst_hmac_user, puc_vht_cap_ie);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (puc_vht_cap_ie[1] < MAC_VHT_CAP_IE_LEN)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_proc_vht_cap_ie::invalid vht cap ie len[%d].}", puc_vht_cap_ie[1]);
        return OAL_FAIL;
    }

    pst_mac_user = &pst_hmac_user->st_user_base_info;

    /* ֧��11ac���Ž��к����Ĵ��� */
    if (OAL_FALSE == mac_mib_get_VHTOptionImplemented(pst_mac_vap))
    {
        return OAL_SUCC;
    }

    pst_mac_vht_hdl = &st_mac_vht_hdl;
    mac_user_get_vht_hdl(pst_mac_user, pst_mac_vht_hdl);

    /* ����˺�������user֧��11ac */
    pst_mac_vht_hdl->en_vht_capable = OAL_TRUE;

#ifdef _PRE_WLAN_FEATURE_11AC2G
    /* ���ƻ�ʵ�������֧��11ac2gģʽ����ص�vht cap */
    if((OAL_FALSE == pst_mac_vap->st_cap_flag.bit_11ac2g)
       && (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band))
    {
        pst_mac_vht_hdl->en_vht_capable = OAL_FALSE;
    }
#endif

    us_msg_idx += MAC_IE_HDR_LEN;

    /* ����VHT capablities info field */
    us_vht_cap_filed_low    = OAL_MAKE_WORD16(puc_vht_cap_ie[us_msg_idx], puc_vht_cap_ie[us_msg_idx + 1]);
    us_vht_cap_filed_high   = OAL_MAKE_WORD16(puc_vht_cap_ie[us_msg_idx + 2], puc_vht_cap_ie[us_msg_idx + 3]);
    ul_vht_cap_field        = OAL_MAKE_WORD32(us_vht_cap_filed_low, us_vht_cap_filed_high);

    /* ����max_mpdu_length �μ�11acЭ�� Table 8-183u*/
    pst_mac_vht_hdl->bit_max_mpdu_length = (ul_vht_cap_field & (BIT1 |BIT0));
    if (0 == pst_mac_vht_hdl->bit_max_mpdu_length)
    {
        pst_mac_vht_hdl->us_max_mpdu_length = 3895;
    }
    else if (1 == pst_mac_vht_hdl->bit_max_mpdu_length)
    {
        pst_mac_vht_hdl->us_max_mpdu_length = 7991;
    }
    else if (2 == pst_mac_vht_hdl->bit_max_mpdu_length)
    {
        pst_mac_vht_hdl->us_max_mpdu_length = 11454;
    }

    /* ����supported_channel_width */
    pst_mac_vht_hdl->bit_supported_channel_width = (ul_vht_cap_field & (BIT3 |BIT2));

    /* ����rx_ldpc */
    pst_mac_vht_hdl->bit_rx_ldpc = ((ul_vht_cap_field & BIT4) >> 4);

    /* ����short_gi_80mhz��short_gi_160mhz֧����� */
    pst_mac_vht_hdl->bit_short_gi_80mhz = ((ul_vht_cap_field & BIT5) >> 5);
    pst_mac_vht_hdl->bit_short_gi_80mhz &= pst_mac_vap->pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn80Implemented;

    pst_mac_vht_hdl->bit_short_gi_160mhz = ((ul_vht_cap_field & BIT6) >> 6);
    pst_mac_vht_hdl->bit_short_gi_160mhz &= pst_mac_vap->pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn160and80p80Implemented;

    /* ����tx_stbc ��rx_stbc */
    pst_mac_vht_hdl->bit_tx_stbc = ((ul_vht_cap_field & BIT7) >> 7);
    pst_mac_vht_hdl->bit_rx_stbc = ((ul_vht_cap_field & (BIT10 | BIT9 | BIT8)) >> 8);

    /* ����su_beamformer_cap��su_beamformee_cap */
    pst_mac_vht_hdl->bit_su_beamformer_cap = ((ul_vht_cap_field & BIT11) >> 11);
    pst_mac_vht_hdl->bit_su_beamformee_cap = ((ul_vht_cap_field & BIT12) >> 12);

    /* ����num_bf_ant_supported */
    pst_mac_vht_hdl->bit_num_bf_ant_supported = ((ul_vht_cap_field & (BIT15 | BIT14 | BIT13)) >> 13);

    pst_mac_user->uc_avail_bf_num_spatial_stream = pst_mac_vht_hdl->bit_num_bf_ant_supported;

    /* ����num_sounding_dim */
    pst_mac_vht_hdl->bit_num_sounding_dim =  ((ul_vht_cap_field & (BIT18 | BIT17 | BIT16)) >> 16);

    /* ����mu_beamformer_cap��mu_beamformee_cap */
    pst_mac_vht_hdl->bit_mu_beamformer_cap = ((ul_vht_cap_field & BIT19) >> 19);
    pst_mac_vht_hdl->bit_mu_beamformee_cap = ((ul_vht_cap_field & BIT20) >> 20);

    /* ����vht_txop_ps */
    pst_mac_vht_hdl->bit_vht_txop_ps = ((ul_vht_cap_field & BIT21) >> 21);
    if (pst_mac_vht_hdl->bit_vht_txop_ps)
    {
        pst_mac_vap->st_cap_flag.bit_txop_ps = 0x1;
    }

    /* ����htc_vht_capable */
    pst_mac_vht_hdl->bit_htc_vht_capable = ((ul_vht_cap_field & BIT22) >> 22);

    /* ����max_ampdu_len_exp */
    pst_mac_vht_hdl->bit_max_ampdu_len_exp = ((ul_vht_cap_field & (BIT25 | BIT24 | BIT23)) >> 23);

    /* ����vht_link_adaptation */
    pst_mac_vht_hdl->bit_vht_link_adaptation = ((ul_vht_cap_field & (BIT27 |BIT26)) >> 26);

    /* ����rx_ant_pattern */
    pst_mac_vht_hdl->bit_rx_ant_pattern = ((ul_vht_cap_field & BIT28) >> 28);

    /* ����tx_ant_pattern */
    pst_mac_vht_hdl->bit_tx_ant_pattern = ((ul_vht_cap_field & BIT29) >> 29);

    us_msg_idx += MAC_VHT_CAP_INFO_FIELD_LEN;

    /* ����VHT Supported MCS Set field */


    /* ����rx_mcs_map; DTS2014112108934 :�޸�rx mcs map������������ */
    us_rx_mcs_map = OAL_MAKE_WORD16(puc_vht_cap_ie[us_msg_idx],puc_vht_cap_ie[us_msg_idx + 1]);
    mac_ie_get_vht_rx_mcs_map((mac_rx_max_mcs_map_stru *)&us_rx_mcs_map,
                              (mac_rx_max_mcs_map_stru *)&(pst_mac_vap->pst_mib_info->st_wlan_mib_vht_sta_config.us_dot11VHTTxMCSMap));
    oal_memcopy(&(pst_mac_vht_hdl->st_rx_max_mcs_map), &us_rx_mcs_map, OAL_SIZEOF(mac_rx_max_mcs_map_stru));

    us_msg_idx += MAC_VHT_CAP_RX_MCS_MAP_FIELD_LEN;

    /* ����rx_highest_supp_logGi_data */
    us_rx_highest_supp_logGi_data = OAL_MAKE_WORD16(puc_vht_cap_ie[us_msg_idx],puc_vht_cap_ie[us_msg_idx + 1]);
    pst_mac_vht_hdl->bit_rx_highest_rate = us_rx_highest_supp_logGi_data & (0x1FFF);

    us_msg_idx += MAC_VHT_CAP_RX_HIGHEST_DATA_FIELD_LEN;

    /* ����tx_mcs_map */
    us_tx_mcs_map = OAL_MAKE_WORD16(puc_vht_cap_ie[us_msg_idx],puc_vht_cap_ie[us_msg_idx + 1]);
    oal_memcopy(&(pst_mac_vht_hdl->st_tx_max_mcs_map), &us_tx_mcs_map, OAL_SIZEOF(mac_tx_max_mcs_map_stru));

    us_msg_idx += MAC_VHT_CAP_TX_MCS_MAP_FIELD_LEN;

    /* ����tx_highest_supp_logGi_data */
    us_tx_highest_supp_logGi_data = OAL_MAKE_WORD16(puc_vht_cap_ie[us_msg_idx],puc_vht_cap_ie[us_msg_idx + 1]);
    pst_mac_vht_hdl->bit_tx_highest_rate = us_tx_highest_supp_logGi_data & (0x1FFF);

    mac_user_set_vht_hdl(pst_mac_user, pst_mac_vht_hdl);
    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_HS20
/*****************************************************************************
 �� �� ��  : hmac_interworking_check
 ��������  : ����������interworking����λ���
 �������  : puc_param ɨ�赽��BSS���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��29��
    ��    ��   : w00346925
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_interworking_check(hmac_vap_stru *pst_hmac_vap,  oal_uint8 *puc_param)
{
    oal_uint8           *puc_extend_cap_ie;
    mac_bss_dscr_stru   *pst_bss_dscr;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap) || OAL_UNLIKELY(OAL_PTR_NULL == puc_param))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_interworking_check:: check failed, null ptr!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_bss_dscr = (mac_bss_dscr_stru *)puc_param;

    if (pst_bss_dscr->ul_mgmt_len < (MAC_80211_FRAME_LEN + MAC_SSID_OFFSET))
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{hmac_interworking_check:: mgmt_len(%d) < (80211_FRAME_LEN+SSID_OFFSET).}", pst_bss_dscr->ul_mgmt_len);
        return OAL_FAIL;
    }

    /* ����interworking ie */
    /*lint -e416*/
    puc_extend_cap_ie = mac_find_ie(MAC_EID_EXT_CAPS, pst_bss_dscr->auc_mgmt_buff + MAC_80211_FRAME_LEN + MAC_SSID_OFFSET, (oal_int32)(pst_bss_dscr->ul_mgmt_len - MAC_80211_FRAME_LEN - MAC_SSID_OFFSET));
    /*lint +e416*/

    if (OAL_PTR_NULL == puc_extend_cap_ie)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{hmac_interworking_check:: puc_extend_cap_ie is NULL, the ul_mgmt_len is %d.}", pst_bss_dscr->ul_mgmt_len);
        return OAL_FAIL;
    }

    /*  δ��⵽interworking����λ������fail */
    if (puc_extend_cap_ie[1] < 4 || !(puc_extend_cap_ie[5] & 0x80))
    {
        pst_hmac_vap->uc_is_interworking = OAL_FALSE;
        return OAL_FAIL;
    }

    pst_hmac_vap->uc_is_interworking = OAL_TRUE;
    return OAL_SUCC;
}
#endif //_PRE_WLAN_FEATURE_HS20


/*lint -e19*/
oal_module_symbol(hmac_config_send_deauth);
oal_module_symbol(hmac_wpas_mgmt_tx);
/*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

