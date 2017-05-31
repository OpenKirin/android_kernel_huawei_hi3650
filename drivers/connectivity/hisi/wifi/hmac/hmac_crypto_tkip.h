/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_crypto_tkip.h
  �� �� ��   : ����
  ��    ��   : g00260350
  ��������   : 2014��3��1��
  ����޸�   :
  ��������   : hmac_crypto_tkip.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��3��1��
    ��    ��   : g00260350
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __HMAC_CRYPTO_FRAME_H__
#define __HMAC_CRYPTO_FRAME_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "mac_vap.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define michael_block(l, r)                     \
        do {                                    \
        r ^= rotl(l, 17);                       \
        l += r;                                 \
        r ^= xswap(l);                          \
        l += r;                                 \
        r ^= rotl(l, 3);                        \
        l += r;                                 \
        r ^= rotr(l, 2);                        \
        l += r;                                 \
        } while (0)
#define IEEE80211_WEP_MICLEN        8   /* trailing MIC */

#define IEEE80211_FC1_DIR_NODS              0x00    /* STA->STA */
#define IEEE80211_FC1_DIR_TODS              0x01    /* STA->AP  */
#define IEEE80211_FC1_DIR_FROMDS            0x02    /* AP ->STA */
#define IEEE80211_FC1_DIR_DSTODS            0x03    /* AP ->AP  */

#define IEEE80211_NON_QOS_SEQ               16      /* index for non-QoS (including management) sequence number space */
#define IEEE80211_FC0_TYPE_MASK             0x0c
#define IEEE80211_FC0_SUBTYPE_QOS           0x80
#define IEEE80211_FC0_TYPE_DATA             0x08


#define WEP_IV_FIELD_SIZE       4       /* wep IV field size */
#define EXT_IV_FIELD_SIZE       4       /* ext IV field size */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

OAL_STATIC OAL_INLINE oal_uint32 rotl(oal_uint32 val, oal_int32 bits)
{
    return (val << bits) | (val >> (32 - bits));
}


OAL_STATIC OAL_INLINE oal_uint32 rotr(oal_uint32 val, oal_int32 bits)
{
    return (val >> bits) | (val << (32 - bits));
}


OAL_STATIC OAL_INLINE oal_uint32 xswap(oal_uint32 val)
{
    return ((val & 0x00ff00ff) << 8) | ((val & 0xff00ff00) >> 8);
}


OAL_STATIC OAL_INLINE oal_uint32 get_le32_split(oal_uint8 b0, oal_uint8 b1, oal_uint8 b2, oal_uint8 b3)
{
    return b0 | (b1 << 8) | (b2 << 16) | (b3 << 24);
}

OAL_STATIC OAL_INLINE oal_uint32 get_le32(const oal_uint8 *p)
{
    return get_le32_split(p[0], p[1], p[2], p[3]);
}
OAL_STATIC OAL_INLINE oal_void put_le32(oal_uint8 *p, oal_uint32 v)
{
    p[0] = (oal_uint8)v;
    p[1] = (oal_uint8)(v >> 8);
    p[2] = (oal_uint8)(v >> 16);
    p[3] = (oal_uint8)(v >> 24);
}


oal_uint32 hmac_crypto_tkip_enmic(wlan_priv_key_param_stru *pst_key, oal_netbuf_stru *pst_netbuf);
oal_uint32 hmac_crypto_tkip_demic(wlan_priv_key_param_stru *pst_key, oal_netbuf_stru *pst_netbuf);



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_crypto_tkip.h */
