/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : oal_aes.h
  �� �� ��   : ����
  ��    ��   : z00237171
  ��������   : 2014��4��18��
  ����޸�   :
  ��������   : oal_aes.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��4��18��
    ��    ��   : z00237171
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OAL_AES_H__
#define __OAL_AES_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_schedule.h"
#include "oal_util.h"
#include "oal_types.h"
#include "oal_net.h"


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define OAL_MMIE_IPN_LEN             6
#define OAL_MMIE_MIC_LEN             8
#define OAL_AES_BLOCK_SIZE          16
#define OAL_AES_BLOCK_LEN           16   /* AES?��?��?��3��?�� */

#define OAL_ETH_ALEN                 6   /* ��?��?��???����3��?�� */

#define OAL_AES_KEYSIZE_128         16
#define OAL_AES_KEYSIZE_192         24
#define OAL_AES_KEYSIZE_256         32

#define OAL_BIP_AAD_LEN             20   /* BIP ADD3��?�� */
//#define OAL_AES_MAX_KEYLENGTH       (15 * 16)
#define OAL_AES_MAX_KEYLENGTH       60

#define OAL_AES_MAX_KEYLENGTH_U32   (OAL_AES_MAX_KEYLENGTH / OAL_SIZEOF(oal_uint32))
#define OAL_MANAGEMENT_FRAME_LEN     292
#define OAL_MGMT_FRAME_MMIE_LEN      18

#define OAL_EID_MMIE                 76
#define OAL_IE_HDR_LEN                2
#define OAL_MAX_IGTK_KEY_INDEX        5
#define OAL_NUM_IGTK                  2

#define oal_host_to_le16(n) (n)
#define oal_host_to_le32(n) (n)
#define oal_le32_to_host(n) (n)

#define OAL_CMAC_TLEN           8    /* CMAC TLen = 64 bits (8 octets) */
#define OAL_AAD_LEN             20   /* BIP ADD3��?�� */


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
/* AES�㷨��Կ�ṹ */
struct oal_aes_key_stru
{
    oal_uint32 ul_key_enc[OAL_AES_MAX_KEYLENGTH];
    oal_uint32 ul_key_dec[OAL_AES_MAX_KEYLENGTH];
    oal_uint32 ul_key_length;
}__OAL_DECLARE_PACKED;
typedef struct oal_aes_key_stru oal_aes_key_stru;

struct oal_aes_ctx_stru
{
    oal_aes_key_stru  key;
    oal_uint8         pn[6];
    oal_uint8         key_idx;
    oal_uint8         resv[1];   /* crypto_buf�ĵ�ַ����4�ֽڶ��룬�㷨Ҫ�� */
    oal_uint8         crypto_buf[6 * OAL_AES_BLOCK_LEN];
}__OAL_DECLARE_PACKED;
typedef struct oal_aes_ctx_stru oal_aes_ctx_stru;


struct oal_mmie_stru
{
    oal_uint8  element_id;
    oal_uint8  length;
    oal_uint16 key_id;
    oal_uint8  sequence_number[OAL_MMIE_IPN_LEN];
    oal_uint8  mic[OAL_MMIE_MIC_LEN];
}__OAL_DECLARE_PACKED;
typedef struct oal_mmie_stru oal_mmie_stru;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_uint32  oal_aes_expand_key(oal_aes_key_stru *pst_aes_key,
                                            OAL_CONST oal_uint8 *in_key,
		                                    unsigned int key_len);
extern oal_uint32  oal_aes_encrypt(oal_aes_key_stru *pst_aes_key,
                                       oal_uint8  *puc_ciphertext,
                                       OAL_CONST oal_uint8  *puc_plaintext);
extern oal_uint32  oal_aes_decrypt(oal_aes_key_stru *pst_aes_key,
                                       oal_uint8  *puc_plaintext,
                                       OAL_CONST oal_uint8  *puc_ciphertext);

#if (!defined(_PRE_PRODUCT_ID_HI110X_HOST))
extern oal_uint32 oal_crypto_bip_enmic(oal_uint8 uc_igtk_keyid, oal_uint8 *pst_igtk_key, oal_uint8 *pst_igtk_seq, oal_netbuf_stru *pst_netbuf, oal_uint16 *pst_frame_len);
#endif
extern oal_uint32 oal_crypto_bip_demic(oal_uint8 uc_igtk_keyid, oal_uint8 *pst_igtk_key, oal_uint8 *pst_igtk_seq, oal_netbuf_stru *pst_netbuf, oal_uint32 *pul_dot11RSNAStatsCMACReplays, oal_uint32 *pul_dot11RSNAStatsCMACICVErrors);









#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_aes.h */
