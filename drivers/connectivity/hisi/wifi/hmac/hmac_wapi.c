/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_wpi_crypt.c
  �� �� ��   : ����
  ��    ��   : z00260280
  ��������   : 2015��5��20��
  ����޸�   :
  ��������   : wpi���ݼӽ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��5��20��
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
#include "oal_types.h"
#include "oal_mem.h"
#include "mac_frame.h"
#include "hmac_wapi_sms4.h"
#include "hmac_wapi_wpi.h"
#include "hmac_wapi.h"
#include "mac_data.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_WAPI_C

#ifdef _PRE_WLAN_FEATURE_WAPI



/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
OAL_CONST oal_uint8 g_auc_wapi_pn_init[WAPI_PN_LEN] = {0x36,0x5c,0x36,0x5c,0x36,0x5c,0x36,
                    0x5c,0x36,0x5c,0x36,0x5c,0x36,0x5c,0x36,0x5c};

OAL_CONST oal_uint8 g_auc_wapi_oui[WAPI_IE_OUI_SIZE] = {0x00,0x14,0x72};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : hmac_wapi_is_qos
 ��������  : �ж��Ƿ�Ϊqos֡
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_bool_enum_uint8  hmac_wapi_is_qos(mac_ieee80211_frame_stru *pst_mac_hdr)
{
    if ((WLAN_DATA_BASICTYPE == pst_mac_hdr->st_frame_control.bit_type)
        && (WLAN_QOS_DATA & pst_mac_hdr->st_frame_control.bit_sub_type))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;

}

/*****************************************************************************
 �� �� ��  : hmac_wapi_calc_mic_data
 ��������  : ����mic���ݣ���Ϊ����mic֮��
 �������  :
 �������  : mic���ݻ������ĳ���
 �� �� ֵ  : ���뵽�Ŀռ�ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��5��21��
    ��    ��   : z00260280
    �޸�����   : ����
    ��    ��   :hmac_rx_get_mac_hdr_len�Ѿ�����4��ַ��������˴����ٿ���
                mic���ݾ��幹�ɼ�<wapiʵʩָ��>5.2.2.3

*****************************************************************************/
oal_uint32 hmac_wapi_calc_mic_data(mac_ieee80211_frame_stru *pst_mac_hdr, oal_uint8 uc_mac_hdr_len, oal_uint8 uc_keyidx, oal_uint8 *puc_payload, oal_uint16 us_pdu_len, oal_uint8 *puc_mic, oal_uint16 us_mic_len)
{
    oal_uint8       us_is_qos;
    oal_uint8      *puc_mic_oringin;

    OAL_MEMZERO(puc_mic, us_mic_len);

    puc_mic_oringin = puc_mic;

    /* frame control */
    oal_memcopy(puc_mic, (oal_uint8 *)&(pst_mac_hdr->st_frame_control), OAL_SIZEOF(pst_mac_hdr->st_frame_control));
    puc_mic[0] &= ~(BIT4 | BIT5 | BIT6);                 /* sub type */
    puc_mic[1] &= ~(BIT3 | BIT4 | BIT5);                 /* retry, pwr Mgmt, more data */
    puc_mic[1] |= BIT6;

    puc_mic += OAL_SIZEOF(pst_mac_hdr->st_frame_control);


    /* addr1 */
    mac_get_address1((oal_uint8 *)pst_mac_hdr, puc_mic);
    puc_mic += OAL_MAC_ADDR_LEN;

    /* addr2 */
    mac_get_address2((oal_uint8 *)pst_mac_hdr, puc_mic);
    puc_mic += OAL_MAC_ADDR_LEN;
#if 0
    /* ���п��� */
    puc_mic[0] &= ~(BIT4 | BIT5 | BIT6);                 /* sub type */
    puc_mic[1] &= ~(BIT3 | BIT4 | BIT5);                 /* retry, pwr Mgmt, more data */
    puc_mic += 2;
#endif
    /* ���п��� */
    OAL_MEMZERO(puc_mic, 2);
    puc_mic[0] = (oal_uint8)(pst_mac_hdr->bit_frag_num);
    puc_mic += 2;

    /* addr3 */
    mac_get_address3((oal_uint8 *)pst_mac_hdr, puc_mic);
    puc_mic += OAL_MAC_ADDR_LEN;

    /* ����addr4 */
    puc_mic += OAL_MAC_ADDR_LEN;

    /* qos ctrl */
    us_is_qos = hmac_wapi_is_qos(pst_mac_hdr);
    if (OAL_TRUE == us_is_qos)
    {
        mac_get_qos_ctrl((oal_uint8 *)pst_mac_hdr, puc_mic);
        puc_mic += MAC_QOS_CTL_LEN;
    }

    /* keyidx + reserve�ܹ�2���ֽ� */
    *puc_mic = uc_keyidx;
    puc_mic += 2;

    /*���pdulen Э��д������ֽ��� */
    *puc_mic = (oal_uint8)((us_pdu_len & 0xff00) >> 8);
    *(puc_mic + 1) = (oal_uint8)(us_pdu_len & 0x00ff);
    puc_mic += 2;

    /************����2����*******************/
    //oal_memcopy(puc_mic, pst_mac_hdr + uc_mac_hdr_len + HMAC_WAPI_HDR_LEN, us_pdu_len);

    puc_mic_oringin += (OAL_TRUE == hmac_wapi_is_qos(pst_mac_hdr))?SMS4_MIC_PART1_QOS_LEN:SMS4_MIC_PART1_NO_QOS_LEN;
    oal_memcopy(puc_mic_oringin, puc_payload, us_pdu_len);

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : hmac_wapi_mic_alloc
 ��������  : ����ռ䣬���ڴ��mic
 �������  :
 �������  : ��
 �� �� ֵ  : ���뵽�Ŀռ�ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��5��21��
    ��    ��   : z00260280
    �޸�����   : ����
    ��    ��

*****************************************************************************/
oal_uint8 *hmac_wapi_mic_alloc(oal_uint8 is_qos, oal_uint16 us_pdu_len, oal_uint16 *pus_mic_len)
{
    oal_uint16      us_mic_part1_len;
    oal_uint16      us_mic_part2_len;
    oal_uint16      us_mic_len;

    us_mic_part1_len = (OAL_TRUE == is_qos)?SMS4_MIC_PART1_QOS_LEN:SMS4_MIC_PART1_NO_QOS_LEN;

    /* ����Э�飬���벻��λ��16�ֽڶ��� */
    us_mic_part2_len = PADDING(us_pdu_len, SMS4_PADDING_LEN);

    us_mic_len = us_mic_part1_len + us_mic_part2_len;

    *pus_mic_len = us_mic_len;

    return OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,us_mic_len, OAL_TRUE);

}

/*****************************************************************************
 �� �� ��  : hmac_wapi_mic_free
 ��������  : �ͷ������mic�ռ�
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��5��21��
    ��    ��   : z00260280
    �޸�����   : ����
    ��    ��

*****************************************************************************/
oal_uint32 hmac_wapi_mic_free(oal_uint8 *puc_mic)
{
    if (OAL_PTR_NULL != puc_mic)
    {
        //TBD oam
        OAL_MEM_FREE(puc_mic, OAL_TRUE);
        return OAL_SUCC;
    }

    return OAL_FAIL;
}

#if 0
oal_uint8 hmac_wapi_get_keyidx(oal_uint8 *puc_wapi_hdr)
{
    return *puc_wapi_hdr;
}
#endif

/*****************************************************************************
 �� �� ��  : hmac_wapi_is_keyidx_valid
 ��������  : �ж�keyidx�Ƿ�Ϸ�
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��2��
    ��    ��   : z00206031
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint8 hmac_wapi_is_keyidx_valid(hmac_wapi_stru *pst_wapi, oal_uint8 uc_keyidx_rx)
{


    if (pst_wapi->uc_keyidx != uc_keyidx_rx
        && OAL_TRUE != pst_wapi->uc_keyupdate_flg)
    {
        OAM_WARNING_LOG3(0, OAM_SF_ANY, "{hmac_wapi_is_keyidx_valid::keyidx==%u, uc_keyidx_rx==%u, update==%u.}",
                                            pst_wapi->uc_keyidx, uc_keyidx_rx, pst_wapi->uc_keyupdate_flg);
        WAPI_RX_IDX_UPDATE_ERR(pst_wapi);
        return OAL_FALSE;
    }

    pst_wapi->uc_keyupdate_flg = OAL_FALSE; /* �������ȡ����־ */

    /* keyû������ */
    if (OAL_TRUE != pst_wapi->ast_wapi_key[uc_keyidx_rx].uc_key_en)
    {

        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_wapi_is_keyidx_valid::keyen==%u.}",
                                        pst_wapi->ast_wapi_key[uc_keyidx_rx].uc_key_en);
        WAPI_RX_IDX_UPDATE_ERR(pst_wapi);
        return OAL_FALSE;
    }

    return OAL_TRUE;
}

/*****************************************************************************
 �� �� ��  : hmac_wapi_is_pn_odd_ucast
 ��������  : ����֡�ж�������ż��ȷ��
 �������  :
 �������  : ��
 �� �� ֵ  : ���Ϊż���򷵻�false
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��5��21��
    ��    ��   : z00260280
    �޸�����   : ����
    ��    ��

*****************************************************************************/
oal_bool_enum_uint8 hmac_wapi_is_pn_odd_ucast(oal_uint8 *puc_pn)
{
    return (oal_bool_enum_uint8)((0 == (*puc_pn & BIT0))?OAL_FALSE:OAL_TRUE);
}

/*****************************************************************************
 �� �� ��  : hmac_wapi_is_pn_bigger
 ��������  : �жϽ��յ���pn�Ƿ���ڼ�¼��pn,���һ����ֵ��λ���С��AP���¼��ֵ�����Բ��ü��
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��5��21��
    ��    ��   : z00260280
    �޸�����   : ����
    ��    ��

*****************************************************************************/
oal_uint8 hmac_wapi_is_pn_bigger(oal_uint8 *puc_pn, oal_uint8 *puc_pn_rx)
{
    oal_uint8   uc_pnidx;

    for(uc_pnidx = SMS4_PN_LEN - 1; uc_pnidx > 0; uc_pnidx--)
    {
        if ((puc_pn[uc_pnidx] != puc_pn_rx[uc_pnidx]))
        {
            if (puc_pn[uc_pnidx] > puc_pn_rx[uc_pnidx])
            {
                OAM_WARNING_LOG2(0, OAM_SF_ANY, "{hmac_wapi_is_pn_bigger::err! puc_pn==%u, puc_pn_rx==%u.}", puc_pn[uc_pnidx] , puc_pn_rx[uc_pnidx]);
                return OAL_FALSE;
            }

            return OAL_TRUE;
        }
    }

    return OAL_TRUE;
}


/*****************************************************************************
 �� �� ��  : hmac_wapi_is_pn_odd_bcast
 ��������  : �鲥֡�ж�������ż��
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��5��21��
    ��    ��   : z00260280
    �޸�����   : ����
    ��    ��

*****************************************************************************/
oal_uint8 hmac_wapi_is_pn_odd_bcast(oal_uint8 *puc_pn)
{
    return OAL_TRUE;
}

/*****************************************************************************
 �� �� ��  : hmac_wapi_pn_update
 ��������  : ÿ�յ�һ��֡������pn
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��5��21��
    ��    ��   : z00260280
    �޸�����   : ����
    ��    ��

*****************************************************************************/
oal_uint8 hmac_wapi_pn_update(oal_uint8 *puc_pn, oal_uint8  uc_inc)
{
    oal_uint32          ul_loop;
    oal_uint32          ul_loop_num;
    oal_uint32          ul_overlow;     /* ��λ */
    oal_uint32         *pul_pn;

    pul_pn = (oal_uint32 *)puc_pn;
    ul_loop_num = WAPI_PN_LEN / OAL_SIZEOF(oal_uint32);
    ul_overlow = uc_inc;

    for(ul_loop = 0; ul_loop < ul_loop_num; ul_loop++)
    {
        if ( *pul_pn > (*pul_pn + ul_overlow))
        {
            *pul_pn    += ul_overlow;
            ul_overlow = 1;     /* �����λ��1 */
        }
        else
        {
            *pul_pn    += ul_overlow;
            break;
        }
        pul_pn++;
    }

    return OAL_TRUE;
}

/*****************************************************************************
 �� �� ��  : hmac_wapi_netbuff_tx_handle
 ��������  : �����Ѿ���Ƭ���߲����Ƭ��netbuff��
             1)����Ѿ���Ƭ�����������������������netbuff�ϵ����ݽ��м��ܴ���
             2)���û�з�Ƭ��������netbuff,�����netbuff�ϵ����ݽ��м��ܴ���
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��5��21��
    ��    ��   : z00260280
    �޸�����   : ����
    ��    ��

*****************************************************************************/
oal_netbuf_stru  *hmac_wapi_netbuff_tx_handle(hmac_wapi_stru *pst_wapi, oal_netbuf_stru  *pst_buf)
{
    oal_uint32           ul_ret;
    oal_netbuf_stru     *pst_netbuf_tmp;    /* ָ����Ҫ�ͷŵ�netbuff */
    oal_netbuf_stru     *pst_netbuf_prev;   /* ָ���Ѿ����ܵ�netbuff */
    oal_netbuf_stru     *pst_buf_first;     /* ָ��δ���ܵ�netbuff */
    //oal_uint16           us_len;

    /* ������wai֡ */
    if (MAC_DATA_WAPI == mac_get_data_type_from_80211(pst_buf, MAC_80211_QOS_HTC_4ADDR_FRAME_LEN))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_wapi_netbuff_tx_handle::wai, dont encrypt!.}");
        return pst_buf;
    }

    ul_ret = pst_wapi->wapi_encrypt(pst_wapi, pst_buf);
    if (OAL_SUCC != ul_ret)
    {
        hmac_free_netbuf_list(pst_buf);
        return OAL_PTR_NULL;
    }

    pst_netbuf_tmp = pst_buf;

    /* ʹnetbuffָ��ָ����һ����Ҫ���ܵķ�Ƭ֡ */
    pst_netbuf_prev = OAL_NETBUF_NEXT(pst_buf);

    if (OAL_PTR_NULL == pst_netbuf_prev)
    {
        //print TODO
        return OAL_PTR_NULL;
    }
    pst_buf_first = pst_netbuf_prev;
    pst_buf = OAL_NETBUF_NEXT(pst_netbuf_prev);

    oal_netbuf_free(pst_netbuf_tmp);

    while(OAL_PTR_NULL != pst_buf)
    {
        ul_ret = pst_wapi->wapi_encrypt(pst_wapi, pst_buf);
        if(OAL_SUCC != ul_ret)
        {
            hmac_free_netbuf_list(pst_buf_first);
            return OAL_PTR_NULL;
        }
        OAL_NETBUF_NEXT(pst_netbuf_prev) = OAL_NETBUF_NEXT(pst_buf);
        pst_netbuf_tmp = pst_buf;
        pst_netbuf_prev = OAL_NETBUF_NEXT(pst_buf);
        if (OAL_PTR_NULL == pst_netbuf_prev)
        {
            //print TODO
            return OAL_PTR_NULL;
        }
        pst_buf = OAL_NETBUF_NEXT(pst_netbuf_prev);

        oal_netbuf_free(pst_netbuf_tmp);

    }
    return pst_buf_first;
}

/*****************************************************************************
 �� �� ��  : hmac_wapi_netbuff_rx_handle
 ��������  : ���մ���ȷ���Ҫ�򵥣���Ϊÿ��ֻ����һ��netbuff��Ҫ����
             ������ܵ�netbuffΪ1�����ܺ��Ϊ0����ô����Ϊ1,������ɺ��Ϊ
             1->0 ��������1ɾ����Ȼ���Ѿ����ܵ�0������
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��5��21��
    ��    ��   : z00260280
    �޸�����   : ����
    ��    ��

*****************************************************************************/
oal_netbuf_stru  *hmac_wapi_netbuff_rx_handle(hmac_wapi_stru *pst_wapi, oal_netbuf_stru  *pst_buf)
{
    oal_uint32                    ul_ret;
    oal_netbuf_stru              *pst_netbuf_tmp;    /* ָ����Ҫ�ͷŵ�netbuff */

    /* �Ǽ���֡�������н��� */
    if(!((oal_netbuf_data(pst_buf))[1] & 0x40))
    {
        return pst_buf;
    }

    ul_ret = pst_wapi->wapi_decrypt(pst_wapi, pst_buf);

    if(OAL_SUCC != ul_ret)
    {
        return OAL_PTR_NULL;
    }

    pst_netbuf_tmp = pst_buf;
    pst_buf = OAL_NETBUF_NEXT(pst_buf);
    oal_netbuf_free(pst_netbuf_tmp);

    return pst_buf;
}

/*****************************************************************************
 �� �� ��  : hmac_wapi_add_key
 ��������  : ����/���� key
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��5��21��
    ��    ��   : z00260280
    �޸�����   : ����
    ��    ��

*****************************************************************************/
oal_uint32 hmac_wapi_add_key(hmac_wapi_stru *pst_wapi, oal_uint8 uc_key_index, oal_uint8 *puc_key)
{
    hmac_wapi_key_stru              *pst_key;



    WAPI_IS_PORT_VALID(pst_wapi) = OAL_TRUE;
    pst_wapi->uc_keyidx = uc_key_index;
    pst_wapi->uc_keyupdate_flg = OAL_TRUE;
    //pst_wapi->ast_wapi_key[uc_key_index].ul_wpi_ek_len = WAPI_KEY_LEN;
    pst_key = &(pst_wapi->ast_wapi_key[uc_key_index]);


    oal_memcopy(pst_key->auc_wpi_ek, puc_key, WAPI_KEY_LEN);
    oal_memcopy(pst_key->auc_wpi_ck, puc_key + WAPI_KEY_LEN, WAPI_KEY_LEN);
    //oal_memcopy(pst_key->auc_wpi_ck, const oal_void * p_src, oal_uint32 ul_size)
    pst_key->uc_key_en = OAL_TRUE;

    /* ����PN */
    oal_memcopy(pst_key->auc_pn_rx, g_auc_wapi_pn_init, WAPI_PN_LEN);
    oal_memcopy(pst_key->auc_pn_tx, g_auc_wapi_pn_init, WAPI_PN_LEN);

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : hmac_wapi_is_wpihdr_valid
 ��������  : ����wpiͷ�ĺϷ���
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��5��21��
    ��    ��   : z00260280
    �޸�����   : ����
    ��    ��

*****************************************************************************/
oal_uint8 hmac_wapi_is_wpihdr_valid(hmac_wapi_stru *pst_wapi, oal_uint8  *puc_wapi_hdr)
{
    oal_uint8 uc_keyidx_rx;
    oal_uint8 *puc_pn_rx;

    uc_keyidx_rx = *puc_wapi_hdr;

    if (OAL_TRUE != hmac_wapi_is_keyidx_valid(pst_wapi, uc_keyidx_rx))
    {
        return OAL_FALSE;
    }

    puc_pn_rx = puc_wapi_hdr + SMS4_KEY_IDX + SMS4_WAPI_HDR_RESERVE;
    if (OAL_TRUE != pst_wapi->wapi_is_pn_odd(puc_pn_rx))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_wapi_is_wpihdr_valid::wapi_is_pn_odd==false.}");
        WAPI_RX_PN_ODD_ERR(pst_wapi, puc_pn_rx);
        return OAL_FALSE;
    }

    /* �˴�Ϊ�طż�⣬ʵ�ʲ����зǳ�Ӱ�����ܣ���ʱ���� */
#if 0
    if (OAL_TRUE != hmac_wapi_is_pn_bigger(pst_wapi->ast_wapi_key[uc_keyidx_rx].auc_pn_rx, puc_pn_rx))
    {
        dump_frame("bigerr! pn::", pst_wapi->ast_wapi_key[uc_keyidx_rx].auc_pn_rx, WAPI_PN_LEN);
        dump_frame("pnrx::", puc_wapi_hdr + SMS4_KEY_IDX + SMS4_WAPI_HDR_RESERVE, WAPI_PN_LEN);
        WAPI_RX_PN_REPLAY_ERR(pst_wapi, puc_pn_rx);
        return OAL_FALSE;
    }
#endif
    return OAL_TRUE;
}

/*****************************************************************************
 �� �� ��  : hmac_wapi_decrypt
 ��������  : �����ݽ��н���
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��5��21��
    ��    ��   : z00260280
    �޸�����   : ����
    ��    ��   : �˺���������ش�����Ҫ��netbuff�ͷŵ�������Ҫ���͵�������д���

*****************************************************************************/
oal_uint32 hmac_wapi_decrypt(hmac_wapi_stru *pst_wapi, oal_netbuf_stru  *pst_netbuf)
{
    oal_netbuf_stru             *pst_netbuff_des   = NULL;
    oal_uint8                   *puc_key_ek     = NULL;
    oal_uint8                   *puc_key_ck     = NULL;
    oal_uint8                    uc_key_index  = 0;
    oal_uint16                   us_pdu_Len    = 0;
    oal_uint8                    auc_calc_mic[SMS4_MIC_LEN];
    oal_uint32                   ul_wapi_result = OAL_SUCC;

    mac_ieee80211_frame_stru     *pst_mac_hdr;
    oal_uint8                    *puc_netbuff;
    oal_uint16                    us_netbuff_len;
    oal_uint8                    *puc_wapi_hdr;
    oal_uint8                     uc_mac_hdr_len;
    oal_uint8                    *puc_pn;
    oal_uint8                    *puc_pdu;
    oal_uint8                    *puc_mic_data;        /* ����Э�飬����mic����Ҫ�����ݣ��� wapiʵʩָ�� ͼ51 */
    oal_uint8                    *puc_mic;
    oal_uint16                    us_mic_len;
    mac_rx_ctl_stru              *pst_rx_ctl;
    mac_rx_ctl_stru             *pst_rx_ctl_in;

#if 0
    /* ָ���쳣�������� */
    if (OAL_PTR_NULL== pst_wapi
        || OAL_PTR_NULL== pst_netbuf)
    {
        return pst_netbuf;
    }
#endif

    WAPI_RX_PORT_VALID(pst_wapi);
    /************ 1. ����ǰ������׼��,��ȡ��ͷָ������ݳ��� ************/
    puc_netbuff = OAL_NETBUF_DATA(pst_netbuf);        //for ut,del temprarily
    //puc_netbuff = pst_netbuf->head;
    us_netbuff_len = (oal_uint16)OAL_NETBUF_LEN(pst_netbuf);

    /* ��ȡmacͷ */
    pst_mac_hdr = (mac_ieee80211_frame_stru *)puc_netbuff;

    /* wapi������֡һ��ΪQOS֡  */
    pst_rx_ctl_in = (mac_rx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf);
    uc_mac_hdr_len = pst_rx_ctl_in->uc_mac_header_len;
    puc_wapi_hdr = (oal_uint8 *)pst_mac_hdr + uc_mac_hdr_len;
    puc_pn = puc_wapi_hdr + SMS4_KEY_IDX + SMS4_WAPI_HDR_RESERVE;
    puc_pdu = puc_pn + SMS4_PN_LEN;

    OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_wpi_decrypt::uc_mac_hdr_len %u!.}", uc_mac_hdr_len);

    if (us_netbuff_len < (oal_uint16)(uc_mac_hdr_len + HMAC_WAPI_HDR_LEN + SMS4_MIC_LEN))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{hmac_wpi_decrypt::ul_netbuff_len %u, machdr len %u err!.}", us_netbuff_len, uc_mac_hdr_len);
        oal_netbuf_free(pst_netbuf);
        WAPI_RX_NETBUF_LEN_ERR(pst_wapi);
        return OAL_FAIL;
    }
    us_pdu_Len = us_netbuff_len - uc_mac_hdr_len - HMAC_WAPI_HDR_LEN - SMS4_MIC_LEN;

    uc_key_index = *puc_wapi_hdr;

    if (HMAC_WAPI_MAX_KEYID <= uc_key_index)
    {
//#ifdef _PRE_WAPI_DEBUG
        //pst_wapi->st_debug.ulRxWpiHdrErr++;
//#endif /* WAPI_DEBUG_MODE */
        WAPI_RX_IDX_ERR(pst_wapi);
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_wpi_decrypt::uc_key_index %u err!.}", uc_key_index);
        oal_netbuf_free(pst_netbuf);
        return OAL_FAIL;
    }

    if (OAL_TRUE != hmac_wapi_is_wpihdr_valid(pst_wapi, puc_wapi_hdr))
    {
//#ifdef _PRE_WAPI_DEBUG
        //pst_wapi->st_debug.ulRxWpiHdrErr++;
//#endif /* WAPI_DEBUG_MODE */
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_wpi_decrypt::hmac_wapi_is_wpihdr_valid err!.}");
        oal_netbuf_free(pst_netbuf);
        return OAL_FAIL;
    }

    /************ 2. ׼���µ�netbuff,������Ž��ܺ������, ��дcb�ֶ� ************/
    pst_netbuff_des = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if (NULL == pst_netbuff_des)
    {
//#ifdef _PRE_WAPI_DEBUG
        //pst_wapi->st_debug.ulMemMallcoFail++;
//#endif /* WAPI_DEBUG_MODE */
        WAPI_RX_MEMALLOC_ERR(pst_wapi);
        oal_netbuf_free(pst_netbuf);
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* �ȿ���macͷ*/
    oal_netbuf_init(pst_netbuff_des,uc_mac_hdr_len);
    oal_netbuf_copydata(pst_netbuf, 0, oal_netbuf_data(pst_netbuff_des), uc_mac_hdr_len);

    /* ����cb */
    pst_rx_ctl = (mac_rx_ctl_stru *)OAL_NETBUF_CB(pst_netbuff_des);
    oal_memcopy(pst_rx_ctl, OAL_NETBUF_CB(pst_netbuf), MAC_TX_CTL_SIZE);

    /************ 3. ����ǰ����Կ׼����PN׼�� ************/
    puc_key_ek = pst_wapi->ast_wapi_key[uc_key_index].auc_wpi_ek;
    hmac_wpi_swap_pn(puc_pn, SMS4_PN_LEN);


    /******************** 4. ����**************************/
    ul_wapi_result = hmac_wpi_decrypt(puc_pn,
                    puc_pdu,
                    (us_pdu_Len + SMS4_MIC_LEN),            /* ��Ҫ���ܵ����ݳ��� */
                    puc_key_ek,
                    (oal_netbuf_data(pst_netbuff_des) + uc_mac_hdr_len));

    if (OAL_SUCC != ul_wapi_result)
    {
        //pkt_mem_free(pucDecBuf - HOST_RX_BUFFER_OFFSET);
        oal_netbuf_free(pst_netbuff_des);
        /* ����֮ǰע�����netbuff�Ƿ������汻�ͷ� */
        oal_netbuf_free(pst_netbuf);
        return OAL_ERR_CODE_WAPI_DECRYPT_FAIL;
    }

    /* mic��ΪУ����������Ҫput */
    oal_netbuf_put(pst_netbuff_des, us_pdu_Len);

    /************ 5. ����mic��������У�� ************/
    puc_mic_data = hmac_wapi_mic_alloc(hmac_wapi_is_qos(pst_mac_hdr), us_pdu_Len, &us_mic_len);
    if (OAL_PTR_NULL == puc_mic_data)
    {
//#ifdef _PRE_WAPI_DEBUG
        //pst_wapi->st_debug.ulMemMallcoFail++;
//#endif /* WAPI_DEBUG_MODE */
        WAPI_RX_MEMALLOC_ERR(pst_wapi);
        oal_netbuf_free(pst_netbuff_des);
        /* ע��netbuff�����Ƿ����ͷŴ��� */
        oal_netbuf_free(pst_netbuf);
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* ����micԤ������ */
    hmac_wapi_calc_mic_data(pst_mac_hdr, uc_mac_hdr_len, uc_key_index, oal_netbuf_data(pst_netbuff_des) + uc_mac_hdr_len ,us_pdu_Len, puc_mic_data, us_mic_len);
    puc_key_ck = pst_wapi->ast_wapi_key[uc_key_index].auc_wpi_ck;
    ul_wapi_result = hmac_wpi_pmac(puc_pn,
                    puc_mic_data,
                    (us_mic_len >> 4) ,
                    puc_key_ck,
                    auc_calc_mic);

    /* ������mic���ͷ�mic data */
    hmac_wapi_mic_free(puc_mic_data);
    if (OAL_SUCC != ul_wapi_result)

    {
        oal_netbuf_free(pst_netbuff_des);

//#ifdef _PRE_WAPI_DEBUG
        //pst_wapi->st_debug.rx_mic_calc_fail++;
//#endif /* WAPI_DEBUG_MODE */
        //WAPI_RX_MIC_ERR(pst_wapi);
        oal_netbuf_free(pst_netbuf);
        return OAL_ERR_CODE_WAPI_MIC_CALC_FAIL;
    }

    puc_mic = oal_netbuf_data(pst_netbuff_des) + uc_mac_hdr_len + us_pdu_Len;
    if (0 != oal_memcmp(puc_mic, auc_calc_mic, SMS4_MIC_LEN))              /* �Ƚ�MIC */
    {
//#ifdef _PRE_WAPI_DEBUG
        //pst_wapi->st_debug.ulRxWpiMicErr++;
//#endif /* WAPI_DEBUG_MODE */

        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_wpi_decrypt::mic check fail!.}");
        WAPI_RX_MIC_ERR(pst_wapi);
        //OAM_ERROR_LOG2(0, OAM_SF_ANY, "{hmac_wpi_decrypt::pst_netbuff_des==%x, pst_netbuf==%x!.}", (oal_uint32)pst_netbuff_des, (oal_uint32)pst_netbuf);
        oal_netbuf_free(pst_netbuff_des);
        oal_netbuf_free(pst_netbuf);
        return OAL_ERR_CODE_WAPI_MIC_CMP_FAIL;
    }

    /* ����ǰ��protected */
    (oal_netbuf_data(pst_netbuff_des))[1] &= ~0x40;

    /* ��дcb */
    pst_rx_ctl->pul_mac_hdr_start_addr = (oal_uint32 *)OAL_NETBUF_HEADER(pst_netbuff_des);
    pst_rx_ctl->uc_mac_header_len  = uc_mac_hdr_len;
    pst_rx_ctl->us_frame_len = (oal_uint16)OAL_NETBUF_LEN(pst_netbuff_des);

    OAL_NETBUF_NEXT(pst_netbuff_des) = OAL_NETBUF_NEXT(pst_netbuf);
    OAL_NETBUF_NEXT(pst_netbuf) = pst_netbuff_des;

    hmac_wapi_pn_update(pst_wapi->ast_wapi_key[pst_wapi->uc_keyidx].auc_pn_rx, pst_wapi->uc_pn_inc);

    OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_wpi_decrypt::OK!.}");
    WAPI_RX_DECRYPT_OK(pst_wapi);
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_wapi_encrypt
 ��������  : �����ݽ��м���,�������֮�������Ƿ��Ƭ��
            ��һ��netbuffΪ����ǰ��û�м��ܵ�netbuff��
            ����ҵ�netbuffΪ���ܹ���netbuff,��ע��!
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��5��21��
    ��    ��   : z00260280
    �޸�����   : ����
    ��    ��

*****************************************************************************/
oal_uint32 hmac_wapi_encrypt(hmac_wapi_stru *pst_wapi, oal_netbuf_stru  *pst_netbuf)
{
    mac_ieee80211_frame_stru        *pst_mac_hdr;
    oal_uint8                        uc_mac_hdr_len;
    oal_uint8                       *puc_mic_data;
    oal_uint16                       us_pdu_Len;
    oal_uint16                       us_mic_len;
    oal_uint8                        uc_key_index;
    oal_uint8                       *puc_key_ck;
    oal_uint8                       *puc_key_ek;
    oal_uint8                        auc_calc_mic[SMS4_MIC_LEN];
    oal_uint8                        auc_pn_swap[SMS4_PN_LEN]; /* ����任���pn,��������mic�ͼ��� */
    oal_netbuf_stru                 *pst_netbuff_des;
    oal_uint8                       *puc_wapi_hdr;
    oal_uint8                       *puc_datain;
    oal_uint32                       ul_result;
    oal_uint8                       *puc_payload;

    /************ 1. ����ǰ������׼��,��ȡ��ͷָ������ݳ��� ************/
    /* ��ȡmacͷ */
    pst_mac_hdr = ((mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf))->pst_frame_header;
    uc_mac_hdr_len =((mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf))->uc_frame_header_length;

    /* ���ü���λ ע�⣬macͷ�漰���ܣ�������Ҫ���ʼ����*/
    mac_set_protectedframe((oal_uint8 *)pst_mac_hdr);

    OAM_WARNING_LOG2(0, OAM_SF_ANY, "{hmac_wapi_encrypt::uc_mac_hdr_len %u! bit_more==%u.}", uc_mac_hdr_len, pst_mac_hdr->st_frame_control.bit_more_frag);
    us_pdu_Len = ((mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf))->us_mpdu_len;
    puc_payload = OAL_NETBUF_DATA(pst_netbuf) + MAC_80211_QOS_HTC_4ADDR_FRAME_LEN;
    /************ 2. ����mic,wapi������֡һ��ΪQOS֡  ************/
    puc_mic_data = hmac_wapi_mic_alloc(hmac_wapi_is_qos(pst_mac_hdr), us_pdu_Len, &us_mic_len);
    if (OAL_PTR_NULL == puc_mic_data)
    {
//#ifdef _PRE_WAPI_DEBUG
        //pst_wapi->st_debug.ultx_memalloc_err++;
//#endif /* WAPI_DEBUG_MODE */
        WAPI_TX_MEMALLOC_ERR(pst_wapi);
        //oal_netbuf_free(pst_netbuf);

        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_wapi_encrypt::hmac_wapi_mic_alloc err!");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* ����micԤ������ */
    uc_key_index = pst_wapi->uc_keyidx;
    hmac_wapi_calc_mic_data(pst_mac_hdr, uc_mac_hdr_len, uc_key_index, puc_payload, us_pdu_Len, puc_mic_data, us_mic_len);
    puc_key_ck = pst_wapi->ast_wapi_key[uc_key_index].auc_wpi_ck;
    oal_memcopy(auc_pn_swap, pst_wapi->ast_wapi_key[uc_key_index].auc_pn_tx, SMS4_PN_LEN);
    //puc_pn = pst_wapi->ast_wapi_key[uc_key_index].auc_pn_tx;
    //hmac_wpi_swap_pn(puc_pn, SMS4_PN_LEN);
    hmac_wpi_swap_pn(auc_pn_swap, SMS4_PN_LEN);
    /* ����mic */
    ul_result = hmac_wpi_pmac(auc_pn_swap,
                    puc_mic_data,
                    (us_mic_len >> 4) ,
                    puc_key_ck,
                    auc_calc_mic);

    hmac_wapi_mic_free(puc_mic_data);
    if (OAL_FAIL == ul_result)
    {
//#ifdef _PRE_WAPI_DEBUG
        //pst_wapi->st_debug.rx_mic_calc_fail++;
//#endif /* WAPI_DEBUG_MODE */
        WAPI_TX_MIC_ERR(pst_wapi);
        //oal_netbuf_free(pst_netbuf);
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_wapi_encrypt::hmac_wpi_pmac mic calc err!");
        return OAL_ERR_CODE_WAPI_MIC_CALC_FAIL;
    }

    /************ 3. ׼���µ�netbuff,������ż��ܺ������, ��дcb,��׼������ǰ������ ************/
    pst_netbuff_des = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if (OAL_PTR_NULL == pst_netbuff_des)
    {
    //#ifdef _PRE_WAPI_DEBUG
        //pst_wapi->st_debug.ulMemMallcoFail++;
    //#endif /* WAPI_DEBUG_MODE */
        WAPI_TX_MEMALLOC_ERR(pst_wapi);
        //oal_netbuf_free(pst_netbuf);
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_wapi_encrypt::pst_netbuff_des alloc err!");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* ��дcb */
    oal_memcopy(OAL_NETBUF_CB(pst_netbuff_des), OAL_NETBUF_CB(pst_netbuf), MAC_TX_CTL_SIZE);

    /* �ȿ���macͷ,Ϊ�˺���hcc�����˴���д���Ŀռ�*/
    oal_netbuf_init(pst_netbuff_des, MAC_80211_QOS_HTC_4ADDR_FRAME_LEN);
    oal_memcopy(OAL_NETBUF_DATA(pst_netbuff_des), pst_mac_hdr, uc_mac_hdr_len);


    //puc_datain = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, ul_netbuff_len + SMS4_MIC_LEN, OAL_TRUE);
    puc_datain = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, us_pdu_Len + SMS4_MIC_LEN, OAL_TRUE);
    if(OAL_PTR_NULL == puc_datain)
    {
        //oal_netbuf_free(pst_netbuf);
        oal_netbuf_free(pst_netbuff_des);
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_wapi_encrypt::puc_datain alloc err!");
        WAPI_TX_MEMALLOC_ERR(pst_wapi);
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }
    //oal_memcopy(puc_datain, OAL_NETBUF_DATA(pst_netbuf), ul_netbuff_len);
    //oal_memcopy(puc_datain + ul_netbuff_len, auc_calc_mic, SMS4_MIC_LEN);
    oal_memcopy(puc_datain, puc_payload, us_pdu_Len);
    /* ����mic */
    oal_memcopy(puc_datain + us_pdu_Len, auc_calc_mic, SMS4_MIC_LEN);

    puc_key_ek = pst_wapi->ast_wapi_key[uc_key_index].auc_wpi_ek;
    /************************ 4. ���� ************************/
    ul_result = hmac_wpi_encrypt(auc_pn_swap,
                    puc_datain,
                    us_pdu_Len + SMS4_MIC_LEN,
                    puc_key_ek,
                    OAL_NETBUF_DATA(pst_netbuff_des) + HMAC_WAPI_HDR_LEN + MAC_80211_QOS_HTC_4ADDR_FRAME_LEN);

    OAL_MEM_FREE(puc_datain, OAL_TRUE);
    if (ul_result != OAL_SUCC)
    {
        oal_netbuf_free(pst_netbuff_des);
        //oal_netbuf_free(pst_netbuf);
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_wapi_encrypt::hmac_wpi_encrypt err==%u!", ul_result);
        return OAL_ERR_CODE_WAPI_ENRYPT_FAIL;
    }
	/* �˴�put��֮��netbuff��lenΪmacͷ+pdulen+sms4+wapi�ĳ��� */
    oal_netbuf_put(pst_netbuff_des, us_pdu_Len + SMS4_MIC_LEN + HMAC_WAPI_HDR_LEN);

    /***************** 5. ��дwapiͷ *****************/
    puc_wapi_hdr = OAL_NETBUF_DATA(pst_netbuff_des) + MAC_80211_QOS_HTC_4ADDR_FRAME_LEN;

    /* ��дWPIͷ -- keyIndex */
    *(puc_wapi_hdr)  = uc_key_index;
    /* ����λ���� */
    *(puc_wapi_hdr + SMS4_KEY_IDX)  = 0;
    /* ��дPN */
    oal_memcopy((puc_wapi_hdr + SMS4_KEY_IDX + SMS4_WAPI_HDR_RESERVE), pst_wapi->ast_wapi_key[uc_key_index].auc_pn_tx, SMS4_PN_LEN);

    /* �ٴ���дcb */
    //oal_netbuf_set_len(pst_netbuff_des, HMAC_WAPI_HDR_LEN + us_pdu_Len + SMS4_MIC_LEN);
    ((mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuff_des))->pst_frame_header = (mac_ieee80211_frame_stru *)OAL_NETBUF_DATA(pst_netbuff_des);

    /* ������mac hdr */
    ((mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuff_des))->us_mpdu_len      = (oal_uint16)(HMAC_WAPI_HDR_LEN + us_pdu_Len + SMS4_MIC_LEN);

    OAL_NETBUF_NEXT(pst_netbuff_des) = OAL_NETBUF_NEXT(pst_netbuf);
    OAL_NETBUF_NEXT(pst_netbuf) = pst_netbuff_des;
    //OAL_NETBUF_NEXT(pst_netbuff_des) = OAL_PTR_NULL;
    /* ����pn */
    hmac_wapi_pn_update(pst_wapi->ast_wapi_key[pst_wapi->uc_keyidx].auc_pn_tx, pst_wapi->uc_pn_inc);
    OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_wapi_encrypt::hmac_wpi_encrypt OK!");

    WAPI_TX_ENCRYPT_OK(pst_wapi);
    return OAL_SUCC;

}



/*****************************************************************************
 �� �� ��  : hmac_wapi_deinit
 ��������  : ȥ��ʼ��wapi����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��26��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_wapi_deinit(hmac_wapi_stru *pst_wapi)
{
    OAL_MEMZERO(pst_wapi, OAL_SIZEOF(hmac_wapi_stru));

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_wapi_reset_port
 ��������  : ��port����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��26��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_wapi_reset_port(hmac_wapi_stru *pst_wapi)
{
    //OAL_MEMZERO(pst_wapi, OAL_SIZEOF(hmac_wapi_stru));
    pst_wapi->uc_port_valid = OAL_FALSE;
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_wapi_init
 ��������  : ��ʼ��wapi����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��26��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_wapi_init(hmac_wapi_stru *pst_wapi, oal_uint8 uc_pairwise)
{
    oal_uint32                  ul_loop;

    hmac_wapi_deinit(pst_wapi);

    if (OAL_TRUE == uc_pairwise)
    {
        pst_wapi->uc_pn_inc = WAPI_UCAST_INC;
        pst_wapi->wapi_is_pn_odd = hmac_wapi_is_pn_odd_ucast;
    }
    else
    {
        pst_wapi->uc_pn_inc = WAPI_BCAST_INC;
        pst_wapi->wapi_is_pn_odd = hmac_wapi_is_pn_odd_bcast;
    }

    for (ul_loop = 0; ul_loop < HMAC_WAPI_MAX_KEYID; ul_loop++)
    {
        pst_wapi->ast_wapi_key[ul_loop].uc_key_en = OAL_FALSE;
        //oal_memcopy(pst_wapi->ast_wapi_key[ul_loop].auc_pn_rx, g_auc_wapi_pn_init, WAPI_PN_LEN);
        //oal_memcopy(pst_wapi->ast_wapi_key[ul_loop].auc_pn_tx, g_auc_wapi_pn_init, WAPI_PN_LEN);
    }

    pst_wapi->uc_port_valid = OAL_FALSE;
    pst_wapi->wapi_decrypt = hmac_wapi_decrypt;
    pst_wapi->wapi_encrypt = hmac_wapi_encrypt;
    pst_wapi->wapi_netbuff_txhandle = hmac_wapi_netbuff_tx_handle;
    pst_wapi->wapi_netbuff_rxhandle = hmac_wapi_netbuff_rx_handle;
    return OAL_SUCC;

}


/*****************************************************************************
 �� �� ��  : alg_autorate_command_print_rate_set
 ��������  : ��ӡproxy arp������Ϣ
 �������  : pst_mac_vap : mac_vapָ��
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��8��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifdef _PRE_WAPI_DEBUG
/*****************************************************************************
 �� �� ��  : hmac_wapi_dump_frame
 ��������  : ��ӡ֡����
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��5��21��
    ��    ��   : z00260280
    �޸�����   : ����
    ��    ��

*****************************************************************************/
oal_void hmac_wapi_dump_frame(oal_uint8 *puc_info, oal_uint8 *puc_data, oal_uint32 ul_len)
{
    oal_uint32 ul_loop;
    OAL_IO_PRINT("%s: \r\n", puc_info);
    for(ul_loop = 0; ul_loop < ul_len; ul_loop += 4)
    {
        OAL_IO_PRINT("%2x ", ul_loop/4);
        OAL_IO_PRINT("%2x %2x %2x %2x \r\n", puc_data[ul_loop], puc_data[ul_loop+1],
                      puc_data[ul_loop+2], puc_data[ul_loop+3]);
    }

}

/*****************************************************************************
 �� �� ��  : hmac_wapi_display_usr_info
 ��������  : ��ӡ�û�wapi����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��5��21��
    ��    ��   : z00260280
    �޸�����   : ����
    ��    ��

*****************************************************************************/
oal_uint32 hmac_wapi_display_usr_info(hmac_user_stru *pst_hmac_user)
{
    oal_uint32                       ul_loop = 0;
    hmac_wapi_stru                  *pst_wapi;
    hmac_wapi_key_stru              *pst_key;
    hmac_wapi_debug                 *pst_debug;

    OAM_WARNING_LOG1(0, OAM_SF_ANY, "wapi port is %u!", WAPI_IS_PORT_VALID(&pst_hmac_user->st_wapi));
    if (OAL_TRUE != WAPI_IS_PORT_VALID(&pst_hmac_user->st_wapi))
    {
        OAL_IO_PRINT("Err! wapi port is not valid!\n");

        return 0;
    }

    pst_wapi = &(pst_hmac_user->st_wapi);
    OAM_WARNING_LOG0(0, OAM_SF_ANY, "keyidx\tupdate\t\tpn_inc\t\n");
    OAM_WARNING_LOG3(0, OAM_SF_ANY, "%u\t%08x%04x\t\n", \
                    pst_wapi->uc_keyidx, \
                    pst_wapi->uc_keyupdate_flg,   \
                    pst_wapi->uc_pn_inc);

    for (ul_loop = 0; ul_loop < HMAC_WAPI_MAX_KEYID; ul_loop++)
    {
        pst_key = &pst_wapi->ast_wapi_key[ul_loop];
        /*lint -e64*/
        hmac_wapi_dump_frame("ek :", pst_key->auc_wpi_ek, WAPI_KEY_LEN);
        hmac_wapi_dump_frame("ck :", pst_key->auc_wpi_ck, WAPI_KEY_LEN);
        hmac_wapi_dump_frame("pn_local_rx :", pst_key->auc_pn_rx, WAPI_PN_LEN);
        hmac_wapi_dump_frame("pn_local_tx :", pst_key->auc_pn_tx, WAPI_PN_LEN);
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "key_en: %u\n",pst_key->uc_key_en);
        /*lint +e64*/
    }

    pst_debug = &pst_wapi->st_debug;
    OAM_WARNING_LOG0(0, OAM_SF_ANY, "TX DEBUG INFO:");
    /*lint -e64 */
    hmac_wapi_dump_frame("pn_rx :", pst_debug->aucrx_pn, WAPI_PN_LEN);
    /*lint +e64 */

    OAM_WARNING_LOG4(0, OAM_SF_ANY, "tx_drop==%u, tx_wai==%u, tx_port_valid==%u, tx_memalloc_fail==%u",
                                                            pst_debug->ultx_ucast_drop,
                                                            pst_debug->ultx_wai,
                                                            pst_debug->ultx_port_valid,
                                                            pst_debug->ultx_memalloc_err);
    OAM_WARNING_LOG3(0, OAM_SF_ANY, "tx_mic_calc_fail==%u, tx_encrypt_ok==%u, tx_memalloc_err==%u",
                                                            pst_debug->ultx_mic_calc_fail,
                                                            //pst_debug->ultx_drop_wai,
                                                            pst_debug->ultx_encrypt_ok,
                                                            pst_debug->ultx_memalloc_err);

    OAM_WARNING_LOG0(0, OAM_SF_ANY, "RX DEBUG INFO:");
    OAM_WARNING_LOG4(0, OAM_SF_ANY, "rx_port_valid==%u, rx_idx_err==%u, rx_netbuff_len_err==%u, rx_idx_update_err==%u",
                                                            pst_debug->ulrx_port_valid,
                                                            pst_debug->ulrx_idx_err,
                                                            pst_debug->ulrx_netbuff_len_err,
                                                            pst_debug->ulrx_idx_update_err);

    OAM_WARNING_LOG4(0, OAM_SF_ANY, "rx_key_en_err==%u, rx_pn_odd_err==%u, rx_pn_replay_err==%u, rx_decrypt_ok==%u",
                                                            pst_debug->ulrx_key_en_err,
                                                            pst_debug->ulrx_pn_odd_err,
                                                            pst_debug->ulrx_pn_replay_err,
                                                             pst_debug->ulrx_decrypt_ok);
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_wapi_display_info
 ��������  : ��ӡwapi����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��5��21��
    ��    ��   : z00260280
    �޸�����   : ����
    ��    ��

*****************************************************************************/
oal_uint32 hmac_wapi_display_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_usr_idx)
{

    hmac_user_stru                  *pst_hmac_user;
    hmac_user_stru                  *pst_hmac_multi_user;


    pst_hmac_multi_user = (hmac_user_stru *)mac_res_get_hmac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_hmac_multi_user)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "Err! multi usr %u does not exist!", pst_mac_vap->us_multi_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "*****************multi usr info start****************");
    hmac_wapi_display_usr_info(pst_hmac_multi_user);
    OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "*****************multi usr info end****************");


    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(us_usr_idx);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "Err! ucast usr %u does not exist!", us_usr_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "*****************ucast usr info start****************");
    hmac_wapi_display_usr_info(pst_hmac_user);
    OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "*****************ucast usr info end****************");

    return OAL_SUCC;
}
#endif



#endif /* #ifdef _PRE_WLAN_FEATURE_WAPI */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

