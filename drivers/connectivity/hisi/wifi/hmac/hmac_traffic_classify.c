/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_traffic_classify.c
  �� �� ��   : ����
  ��    ��   : wanghao 00357635
  ��������   : 2015.9.8
  ����޸�   :
  ��������   : ��������ҵ��ʶ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015.9.8
    ��    ��   : wanghao 00357635
    �޸�����   : �����ļ�
******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN

/*****************************************************************************
  1ͷ�ļ�����
*****************************************************************************/

#include "hmac_traffic_classify.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_TRAFFIC_CLASSIFY_C

/*****************************************************************************
  2�궨��
*****************************************************************************/
#define RTP_VERSION                 2           /* RTPЭ��汾�ţ�ռ2λ����ǰЭ��汾��Ϊ2 */
#define RTP_VER_SHIFT               6           /* RTPЭ��汾��λ���� */
#define RTP_CSRC_MASK               0x0f        /* CSRC��������ռ4λ��ָʾCSRC��ʶ���ĸ��� */
#define RTP_CSRC_LEN_BYTE           4           /* ÿ��CSRC��ʶ��ռ32λ����4�ֽ� */
#define RTP_HDR_LEN_BYTE            12          /* RTP֡ͷ�̶��ֽ���(������CSRC�ֶ�) */
#define TCP_HTTP_VI_LEN_THR         1000        /* HTTP��Ƶ�����ĳ�����ֵ */
#define JUDGE_CACHE_LIFETIME        1           /* ��ʶ�����ʧЧʱ��: 1s */
#define IP_FRAGMENT_MASK            0x1FFF      /* IP��ƬFragment Offset�ֶ� */
/* RTP Payload_Type ���:RFC3551 */
#define RTP_PT_VO_G729              18          /* RTP�غ�����:18-Audio-G729 */
#define RTP_PT_VI_CELB              25          /* RTP�غ�����:25-Video-CelB */
#define RTP_PT_VI_JPEG              26          /* RTP�غ�����:26-Video-JPEG */
#define RTP_PT_VI_NV                28          /* RTP�غ�����:28-Video-nv */
#define RTP_PT_VI_H261              31          /* RTP�غ�����:31-Video-H261 */
#define RTP_PT_VI_MPV               32          /* RTP�غ�����:32-Video-MPV */
#define RTP_PT_VI_MP2T              33          /* RTP�غ�����:33-Video-MP2T */
#define RTP_PT_VI_H263              34          /* RTP�غ�����:34-Video-H263 */
/* HTTP��ý��˿� */
#define HTTP_PORT_80                80          /* HTTPЭ��Ĭ�϶˿ں�80 */
#define HTTP_PORT_8080              8080        /* HTTPЭ��Ĭ�϶˿ں�8080 */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


/*****************************************************************************
 �� �� ��  : hmac_tx_add_cfm_traffic
 ��������  : ���û���ʶ��ҵ�������ʶ���¼��
 �������  : hmac�û��ṹ��ָ�룬TIDָ�룬hmac_tx_major_flow_stru�ṹ��ָ��
 �������  : 
 �� �� ֵ  : �ɹ�����OAL_SUCC,ʧ�ܷ���OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.����: 2015.09.16
    ����: wanghao(w00357635)
    �޸�����: �����º���
*****************************************************************************/

OAL_STATIC oal_uint32 hmac_tx_add_cfm_traffic(hmac_user_stru *pst_hmac_user, oal_uint8 uc_tid, hmac_tx_major_flow_stru *pst_max)
{    
    oal_uint32  ul_time_stamp   = 0;
    oal_uint8   uc_mark         = 0;
    oal_uint8   uc_traffic_idx  = 0;

    hmac_tx_cfm_flow_stru *pst_cfm_info;
    
    if (MAX_CONFIRMED_FLOW_NUM == pst_hmac_user->uc_cfm_num)
    {
        /* ��ʶ���б����������б����ʱ��û��������ҵ������滻 */        
        ul_time_stamp = pst_hmac_user->ast_cfm_flow_list[uc_traffic_idx].ul_last_jiffies;

        for (uc_traffic_idx = 1; uc_traffic_idx < MAX_CONFIRMED_FLOW_NUM; uc_traffic_idx++)
        {
            pst_cfm_info = (pst_hmac_user->ast_cfm_flow_list + uc_traffic_idx);
            /*lint -e718 */ /*lint -e746 */
            if (oal_time_after(ul_time_stamp, pst_cfm_info->ul_last_jiffies))
            {
                ul_time_stamp = pst_cfm_info->ul_last_jiffies;
                uc_mark = uc_traffic_idx;
            }
            /*lint +e718 */ /*lint +e746 */
        }
    }
    else
    {
        /* ��ʶ���б������ҵ��ɼ�¼��index */
        for (uc_traffic_idx = 0; uc_traffic_idx < MAX_CONFIRMED_FLOW_NUM; uc_traffic_idx++)
        {
            pst_cfm_info = (pst_hmac_user->ast_cfm_flow_list + uc_traffic_idx);
            if (OAL_FALSE == pst_cfm_info->us_cfm_flag)
            {
                uc_mark = uc_traffic_idx;
                pst_hmac_user->uc_cfm_num++;
                pst_cfm_info->us_cfm_flag = OAL_TRUE;
                break;
            }
        }
    }
    
    /* �����б� */
    pst_cfm_info = (pst_hmac_user->ast_cfm_flow_list + uc_mark);
    
    oal_memcopy(&pst_cfm_info->st_cfm_flow_info, 
                &pst_max->st_flow_info, 
                OAL_SIZEOF(hmac_tx_flow_info_stru));

    pst_cfm_info->us_cfm_tid      = uc_tid;
    pst_cfm_info->ul_last_jiffies = OAL_TIME_JIFFY;
    
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_tx_traffic_judge
 ��������  : ����Ҫҵ�����ҵ��ʶ����
 �������  : hmac�û��ṹ��ָ�룬��Ҫҵ��ṹ��ָ�룬TIDָ��
 �������  : TID
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.����: 2015.11.26
    ����: wanghao(w00357635)
    �޸�����: �����º���
  2.����: 2015.12.26
    ����: wanghao(w00357635)
    �޸�����: TCPʶ���ܲü�
*****************************************************************************/
OAL_STATIC oal_uint32 hmac_tx_traffic_judge(
                hmac_user_stru *pst_hmac_user, 
                hmac_tx_major_flow_stru *pst_major_flow, 
                oal_uint8 *puc_tid)
{
    oal_uint32                  ul_ret = OAL_FAIL;
    oal_uint8                   uc_cache_idx;
    oal_uint32                  ul_pt;
    
    hmac_tx_judge_list_stru     *pst_judge_list = &(pst_hmac_user->st_judge_list);
    hmac_tx_judge_info_stru     *pst_judge_info;
    
    /* ��Ҫҵ��֡ΪUDP֡������RTP֡��� */
    for (uc_cache_idx = 0; uc_cache_idx < MAX_JUDGE_CACHE_LENGTH; uc_cache_idx++)
    {
        pst_judge_info = (hmac_tx_judge_info_stru*)(pst_judge_list->ast_judge_cache + uc_cache_idx);
        
        if (!oal_memcmp(&pst_judge_info->st_flow_info, 
                         &pst_major_flow->st_flow_info, 
                         OAL_SIZEOF(hmac_tx_flow_info_stru)))
        {
            /* RTP֡�жϱ�׼:versionλ����Ϊ2��SSRC��PT���ֲ��䣬��֡���ȴ���RTP��ͷ���� */
            if ((RTP_VERSION != (pst_judge_info->uc_rtpver >> RTP_VER_SHIFT))
                || (pst_major_flow->ul_rtpssrc      != pst_judge_info->ul_rtpssrc)
                || (pst_major_flow->ul_payload_type != pst_judge_info->ul_payload_type)
                || (pst_major_flow->ul_average_len  < (oal_uint32)(pst_judge_info->uc_rtpver & RTP_CSRC_MASK) * RTP_CSRC_LEN_BYTE + RTP_HDR_LEN_BYTE))
            {
                pst_hmac_user->st_judge_list.ul_to_judge_num = 0;   /* ʶ��ʧ�ܣ���ն��� */
                return OAL_FAIL;                            
            }
        }
    }

    ul_pt = (pst_major_flow->ul_payload_type & (~BIT7));        
    if (ul_pt <= RTP_PT_VO_G729)    /* ����PayloadType�ж�RTP�غ����� */
    {
        *puc_tid = WLAN_TIDNO_VOICE;
    }
    else if ((RTP_PT_VI_CELB == ul_pt) 
              || (RTP_PT_VI_JPEG == ul_pt) 
              || (RTP_PT_VI_NV == ul_pt) 
              || ((RTP_PT_VI_H261 <= ul_pt) && (ul_pt <= RTP_PT_VI_H263)))
    {
        *puc_tid = WLAN_TIDNO_VIDEO;         
    }
    
    /* ʶ��ɹ��������û���ʶ�����б� */    
    if ((WLAN_TIDNO_VOICE == *puc_tid) || (WLAN_TIDNO_VIDEO == *puc_tid))
    {
        ul_ret = hmac_tx_add_cfm_traffic(pst_hmac_user, *puc_tid, pst_major_flow);
    }
    pst_hmac_user->st_judge_list.ul_to_judge_num = 0;   /* ʶ����ɣ���ն��� */            
    
    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : hmac_tx_find_major_traffic
 ��������  : �ҵ���ʶ���������Ҫҵ��
 �������  : hmac�û��ṹ��ָ�룬TIDָ��
 �������  : 
 �� �� ֵ  : �ɹ�����OAL_SUCC��ʧ�ܷ���OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.����: 2015.11.26
    ����: wanghao(w00357635)
    �޸�����: �����º���
*****************************************************************************/
OAL_STATIC oal_uint32 hmac_tx_find_major_traffic(hmac_user_stru *pst_hmac_user, oal_uint8 *puc_tid)
{
    oal_uint8                       uc_cache_idx_i; 
    oal_uint8                       uc_cache_idx_j;

    hmac_tx_major_flow_stru         st_mark; 
    hmac_tx_major_flow_stru         st_max;

    hmac_tx_judge_list_stru         *pst_judge_list = &(pst_hmac_user->st_judge_list);
    hmac_tx_judge_info_stru         *pst_judge_info;

    /* ��ʼ�� */
    st_max.ul_wait_check_num  = 0;    
        
    /* ���г�ʱ����ն��м�¼ */
    if (((oal_int32)pst_judge_list->ul_jiffies_end - (oal_int32)pst_judge_list->ul_jiffies_st) > (JUDGE_CACHE_LIFETIME * OAL_TIME_HZ))  /* ǿ��ת��Ϊlong��ֹjiffies��� */
    {        
        pst_hmac_user->st_judge_list.ul_to_judge_num = 0;    /* ��ն��� */
        return OAL_FAIL;
    }

    /* ����������δ��ʱ */    
    for (uc_cache_idx_i = 0; uc_cache_idx_i < (MAX_JUDGE_CACHE_LENGTH >> 1); uc_cache_idx_i++)
    {
        pst_judge_info = (hmac_tx_judge_info_stru*)(pst_judge_list->ast_judge_cache + uc_cache_idx_i);
        
        if (OAL_FALSE == pst_judge_info->uc_flag)
        {
            continue;
        }

        pst_judge_info->uc_flag = OAL_FALSE;
        oal_memcopy(&st_mark, pst_judge_info, OAL_SIZEOF(hmac_tx_judge_info_stru));
        st_mark.ul_wait_check_num = 1; 

        for (uc_cache_idx_j = 0; uc_cache_idx_j < MAX_JUDGE_CACHE_LENGTH; uc_cache_idx_j++)
        {
            pst_judge_info = (hmac_tx_judge_info_stru*)(pst_judge_list->ast_judge_cache + uc_cache_idx_j);
            
            if ((OAL_TRUE == pst_judge_info->uc_flag)
                 && !oal_memcmp(&pst_judge_info->st_flow_info, 
                                &st_mark.st_flow_info, 
                                OAL_SIZEOF(hmac_tx_flow_info_stru)))
            {
                pst_judge_info->uc_flag     = OAL_FALSE;
                st_mark.ul_average_len      += pst_judge_info->ul_len;
                st_mark.ul_wait_check_num   += 1;                     
            }

            if (st_mark.ul_wait_check_num > st_max.ul_wait_check_num)
            {
                oal_memcopy(&st_max, &st_mark, OAL_SIZEOF(hmac_tx_major_flow_stru));
                if (st_max.ul_wait_check_num >= (MAX_JUDGE_CACHE_LENGTH >> 1))
                {
                    /* ���ҵ���Ҫҵ���������ؼ������� */
                    st_max.ul_average_len = st_max.ul_average_len / st_max.ul_wait_check_num;
                    return hmac_tx_traffic_judge(pst_hmac_user, &st_max, puc_tid);
                }
            }                
        }
    }
    
    if (st_max.ul_wait_check_num < (MAX_JUDGE_CACHE_LENGTH >> 2))
    {
        /* ��Ϊû����Ҫҵ���� */
        pst_hmac_user->st_judge_list.ul_to_judge_num = 0;    /* ��ն��� */
        return OAL_FAIL;
    }

    st_max.ul_average_len = st_max.ul_average_len / st_max.ul_wait_check_num;
    return hmac_tx_traffic_judge(pst_hmac_user, &st_max, puc_tid);
}

/*****************************************************************************
 �� �� ��  : hmac_tx_traffic_classify
 ��������  : ���������ݰ����д���:
                ��ҵ���ѱ�ʶ��ֱ�ӷ���TID, ������ȡ��ͷ��Ϣ�������������
 �������  : netbuff CB�ֶ�ָ�룬ipͷָ�룬TIDָ��
 �������  : 
 �� �� ֵ  : 
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.����: 2015.11.26
    ����: wanghao(w00357635)
    �޸�����: �����º���
  2.����: 2015.12.26
    ����: wanghao(w00357635)
    �޸�����: TCPҵ��ʶ���ܲü�
*****************************************************************************/
oal_void hmac_tx_traffic_classify(
                mac_tx_ctl_stru     *pst_tx_ctl,
                mac_ip_header_stru  *pst_ip, 
                oal_uint8           *puc_tid)
{
    udp_hdr_stru                *pst_udp_hdr;
    hmac_tx_rtp_hdr             *pst_rtp_hdr;
    hmac_tx_flow_info_stru       st_flow_info;

    hmac_tx_judge_list_stru     *pst_judge_list;
    hmac_tx_judge_info_stru     *pst_judge_info;
    hmac_tx_cfm_flow_stru       *pst_cfm_info;

    oal_uint8                    uc_loop;
    oal_uint32                   ul_ret;
    hmac_user_stru              *pst_hmac_user  = (hmac_user_stru *)mac_res_get_hmac_user(MAC_GET_CB_TX_USER_IDX(pst_tx_ctl));

    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "hmac_tx_traffic_classify::cannot find hmac_user_stru!");
        return;
    }

    /* ���ܲü���ֻ����UDP���ģ��Լ�ʶ��WifiDisplay RTSPҵ��ΪVI */
    if (MAC_UDP_PROTOCAL != pst_ip->uc_protocol)
    {
        if (MAC_TCP_PROTOCAL == pst_ip->uc_protocol)
        {
            mac_tcp_header_stru *pst_tcp_hdr = (mac_tcp_header_stru *)(pst_ip + 1);
            
            /* ʶ��WifiDisplay RTSPҵ��ΪVI */
            if (OAL_NTOH_16(MAC_WFD_RTSP_PORT) == pst_tcp_hdr->us_sport)
            {
            	*puc_tid = WLAN_TIDNO_VIDEO;
            	return;
            }
        }
        return;
    }
    
    /* ��ΪIP��Ƭ֡��û�ж˿ںţ�ֱ�ӷ��� */
    if(0 != (OAL_NTOH_16(pst_ip->us_frag_off) & IP_FRAGMENT_MASK))
    {
        return;
    }
    
    pst_udp_hdr = (udp_hdr_stru *)(pst_ip + 1);                         /* ƫ��һ��IPͷ��ȡUDPͷ */

    /* ��ȡ��Ԫ�� */ 
    st_flow_info.us_dport = pst_udp_hdr->us_des_port;
    st_flow_info.us_sport = pst_udp_hdr->us_src_port;  
    st_flow_info.ul_dip   = pst_ip->ul_daddr;
    st_flow_info.ul_sip   = pst_ip->ul_saddr;
    st_flow_info.ul_proto = (oal_uint32)(pst_ip->uc_protocol);

    /* �����������û���ʶ��ҵ��ֱ�ӷ���TID */
    for (uc_loop = 0; uc_loop < pst_hmac_user->uc_cfm_num; uc_loop++)
    {
        pst_cfm_info = (hmac_tx_cfm_flow_stru *)(pst_hmac_user->ast_cfm_flow_list + uc_loop);
        
        if (!oal_memcmp(&pst_cfm_info->st_cfm_flow_info, 
                        &st_flow_info, 
                        OAL_SIZEOF(hmac_tx_flow_info_stru)))
        {            
            *puc_tid = (oal_uint8)(pst_cfm_info->us_cfm_tid);
            pst_cfm_info->ul_last_jiffies = OAL_TIME_JIFFY;   /* ����ҵ����������ʱ�� */
            return;
        }
    }

    /* ������δʶ�𣬴����û���ʶ����� */
    pst_judge_list = &(pst_hmac_user->st_judge_list);
    pst_judge_info = (hmac_tx_judge_info_stru *)(pst_judge_list->ast_judge_cache + pst_judge_list->ul_to_judge_num);
    
    if (MAX_JUDGE_CACHE_LENGTH <= pst_judge_list->ul_to_judge_num)  /* ����������ʶ������е�����������¼ */
    {
        return; 
    }

    pst_judge_list->ul_jiffies_end  = OAL_TIME_JIFFY;       /* ������������ʱ�� */
    if (0 == pst_judge_list->ul_to_judge_num)               /* ������Ϊ�� */
    {        
        pst_judge_list->ul_jiffies_st  = OAL_TIME_JIFFY;    /* ���¶��в���ʱ�� */
    }
    pst_judge_list->ul_to_judge_num += 1;                   /* ���¶��г��� */
    
    OAL_MEMZERO(pst_judge_info, OAL_SIZEOF(hmac_tx_judge_info_stru));    
    oal_memcopy(&(pst_judge_info->st_flow_info), 
                &st_flow_info, 
                OAL_SIZEOF(hmac_tx_flow_info_stru));
    
    pst_rtp_hdr = (hmac_tx_rtp_hdr *)(pst_udp_hdr + 1);                 /* ƫ��һ��UDPͷ��ȡRTPͷ */

    pst_judge_info->uc_flag         = OAL_TRUE;
    //pst_judge_info->uc_udp_flag     = OAL_TRUE;
    pst_judge_info->ul_len          = OAL_NET2HOST_SHORT(pst_ip->us_tot_len) - OAL_SIZEOF(mac_ip_header_stru) - OAL_SIZEOF(udp_hdr_stru);
    pst_judge_info->uc_rtpver       = pst_rtp_hdr->uc_version_and_CSRC;
    pst_judge_info->ul_payload_type = (oal_uint32)(pst_rtp_hdr->uc_payload_type);
    pst_judge_info->ul_rtpssrc      = pst_rtp_hdr->ul_SSRC;

    /* ����ʶ�����������������ȡ������Ҫҵ�񲢽���ҵ��ʶ�� */
    if (MAX_JUDGE_CACHE_LENGTH <= pst_judge_list->ul_to_judge_num)    /* "<=":��ֹ���̲���ʹ��ֵ���ڴ�ʶ����г��ȶ����ڴ� */
    {
        ul_ret = hmac_tx_find_major_traffic(pst_hmac_user, puc_tid);
        if (OAL_SUCC != ul_ret)
        {
            OAM_INFO_LOG0(0, OAM_SF_TX, "hmac_tx_traffic_classify::the classify process failed.");
        }
    }    
}

/*lint -e19*/
oal_module_symbol(hmac_tx_traffic_classify);
/*lint +e19*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

