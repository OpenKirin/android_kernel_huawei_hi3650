





/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "IpComm.h"
#include  "IpIpmGlobal.h"
#include  "msp_at.h"
#include  "msp_diag.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_IPCOMM_C    /*���޸�*/
/*lint +e767*/

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

VOS_UINT8 g_aucNdAllNodesMulticaseAddr[IP_IPV6_ADDR_LEN] = {0xff, 0x02, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x01};
VOS_UINT8 g_aucNdAllRoutersMulticaseAddr[IP_IPV6_ADDR_LEN] = {0xff, 0x02, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x02};

VOS_UINT8 g_aucNdAllNodesMacAddr[IP_MAC_ADDR_LEN] = {0x33, 0x33, 0x00, 0x00, 0x00, 0x01};
VOS_UINT8 g_aucNdAllRoutersMacAddr[IP_MAC_ADDR_LEN] = {0x33, 0x33, 0x00, 0x00, 0x00, 0x02};


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : ND_CheckEpsIdValid
 ��������  : ����link-local��ַ
 �������  : VOS_UINT8 *pucLinkLocalAddr
             VOS_UINT8 *pucIfId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��7��
    ��    ��   : 00145177
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��1��10��
    ��    ��   : y00151394
    �޸�����   : DSDA��������޸ġ�EpsIdΪ��2bitΪModemID����6bitΪEpsbId��

*****************************************************************************/
VOS_UINT32 ND_CheckEpsIdValid(VOS_UINT8 ucExEpsId)
{
    VOS_UINT8       ucEpsId;
    VOS_UINT16      usModemId;

    usModemId = ND_GET_MODEMID_FROM_EXEPSID(ucExEpsId);
    if (usModemId >= MODEM_ID_BUTT)
    {
        return PS_FAIL;
    }

    ucEpsId = ND_GET_EPSID_FROM_EXEPSID(ucExEpsId);
    if ((ucEpsId < ND_MIN_EPSB_ID)
                || (ucEpsId > ND_MAX_EPSB_ID))
    {
        return IP_FAIL;
    }

    return IP_SUCC;
}

/*****************************************************************************
 �� �� ��  : IP_BuildLinkLocalAddr
 ��������  : ����link-local��ַ
 �������  : VOS_UINT8 *pucLinkLocalAddr
             VOS_UINT8 *pucIfId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��7��
    ��    ��   : 00145177
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IP_BuildLinkLocalAddr
(
    VOS_UINT8 *pucLinkLocalAddr,
    const VOS_UINT8 *pucIfId
)
{
    /* ����link-local address */
    IP_SetUint16Data(pucLinkLocalAddr, IP_IPV6_LINK_LOCAL_PREFIX);
    IP_MEM_CPY(&pucLinkLocalAddr[ND_IPV6_IF_OFFSET], pucIfId, ND_IPV6_IF_LEN);
}

/*****************************************************************************
 �� �� ��  : IP_BuildIPv6Header
 ��������  : ΪICMPv6��Ϣ����IP header����֧����չͷ
 �������  :
             VOS_UINT8                  *pucIpv6
             IPV6_PSEDUOHEADER_STRU     *pstPseduoHeader
             VOS_UINT8                  *pucInterfaceId
             VOS_UINT32                 ulUpperLength
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��7��
    ��    ��   : 00145177
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IP_BuildIPv6Header
(
    VOS_UINT8               *pucIpv6,
    IPV6_PSEDUOHEADER_STRU  *pstPseduoHeader,
    const VOS_UINT8         *pucInterfaceId,
    VOS_UINT32               ulUpperLength
)
{
    VOS_UINT8    aucLinkLocalAddr[IP_IPV6_ADDR_LEN] = {0};

    /* ����link-local address */
    IP_BuildLinkLocalAddr(aucLinkLocalAddr, pucInterfaceId);

    /* ����IP�汾�� */
    *pucIpv6 = IP_VERSION_6 << 4;

    /* ����Payload��û����չͷ */
    IP_SetUint16Data(pucIpv6 + IP_IPV6_BASIC_HEAD_PAYLOAD_OFFSET, ulUpperLength);

    /* ����next header */
    *(pucIpv6 + IP_IPV6_BASIC_HEAD_NEXT_HEAD_OFFSET) = IP_HEAD_PROTOCOL_ICMPV6;

    /* Hop Limit 255 */
    *(pucIpv6 + IP_IPV6_BASIC_HOP_LIMIT_OFFSET) = IP_IPV6_ND_HOP_LIMIT;

    IP_MEM_CPY(pucIpv6 + IP_IPV6_SRC_ADDR_OFFSET, aucLinkLocalAddr, IP_IPV6_ADDR_LEN);
    IP_MEM_CPY(pucIpv6 + IP_IPV6_DST_ADDR_OFFSET, g_aucNdAllRoutersMulticaseAddr, IP_IPV6_ADDR_LEN);

    /* Ϊ����checksum����pseudo-header */
    PS_MEM_CPY(pstPseduoHeader->aucIPSrc, aucLinkLocalAddr, IP_IPV6_ADDR_LEN);
    PS_MEM_CPY(pstPseduoHeader->aucIPDes, g_aucNdAllRoutersMulticaseAddr, IP_IPV6_ADDR_LEN);
    IP_SetUint32Data((VOS_UINT8*)&pstPseduoHeader->ulUpperLength, ulUpperLength);
    pstPseduoHeader->ucNextHead = IP_HEAD_PROTOCOL_ICMPV6;

}

/*****************************************************************************
 Function Name   : IP_ND_FormIPv6HeaderMsg
 Description     : IPv6��ͷ����
 Input           : aucSrcIPAddr --- ԴIP��ַ
                   aucDstIPAddr --- Ŀ��IP��ַ
                   ulPduLen     --- ��Ч���س���
 Output          : pucData --- ���Ļ���ָ��
 Return          :

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
/*lint -e830*/
/*lint -e438*/
VOS_VOID IP_ND_FormIPv6HeaderMsg
(
    const VOS_UINT8                    *aucSrcIPAddr,
    const VOS_UINT8                    *aucDstIPAddr,
    VOS_UINT32                          ulPduLen,
    VOS_UINT8                          *pucData,
    VOS_UINT8                           ucType
)
{
    /* �汾 */
    *pucData = (VOS_UINT8)((IP_VERSION_6 << IP_MOVEMENT_4_BITS) & IP_IPDATA_HIGH_4_BIT_MASK);
    pucData++;

    /* �������͡�����ǩ */
    pucData += 3;

    /* ��Ч���س��� */
    IP_SetUint16Data(pucData, (VOS_UINT16)ulPduLen);
    pucData += 2;

    /* ��һ��ͷ */
    *pucData = ucType;
    pucData++;

    /* ������ */
    *pucData = IP_IPV6_ND_HOP_LIMIT;
    pucData++;

    /* Դ��ַ */
    IP_MEM_CPY( pucData,
                aucSrcIPAddr,
                IP_IPV6_ADDR_LEN);
    pucData += IP_IPV6_ADDR_LEN;

    /* Ŀ�ĵ�ַ */
    IP_MEM_CPY( pucData,
                aucDstIPAddr,
                IP_IPV6_ADDR_LEN);
    pucData += IP_IPV6_ADDR_LEN;
}
/*lint +e830*/
/*lint +e438*/
/*****************************************************************************
 �� �� ��  : IP_IsValidRAPacket
 ��������  : RA�Ϸ��Լ��
 �������  : const VOS_UINT8                    *pucIpMsg
             VOS_UINT32                         ulTypeOffset
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��7��
    ��    ��   : 00145177
    �޸�����   : �����ɺ���

*****************************************************************************/
IP_BOOL_ENUM_UINT8 IP_IsValidRAPacket
(
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT32                         ulTypeOffset
)
{
    VOS_UINT32                          ulTmp;

    IP_ASSERT_RTN(VOS_NULL_PTR != pucIpMsg, IP_FALSE);

    /* link-local source address */
    IP_GetUint16Data(ulTmp, pucIpMsg + IP_IPV6_SRC_ADDR_OFFSET);
    if(IP_IPV6_LINK_LOCAL_PREFIX != (ulTmp & IP_IPV6_LINK_LOCAL_MASK))
    {
        IPND_ERROR_LOG1(ND_TASK_PID, "IP_IsValidRAPacket: Illegal source address:!", ulTmp);
        return IP_FALSE;
    }

    /* Hop Limit 255 */
    ulTmp = *(pucIpMsg + IP_IPV6_BASIC_HOP_LIMIT_OFFSET);
    if(IP_IPV6_ND_HOP_LIMIT != ulTmp)
    {
        IPND_ERROR_LOG1(ND_TASK_PID, "IP_IsValidRAPacket: Illegal Hop Limit:!", ulTmp);
        return IP_FALSE;
    }

    /* CODE 0 */
    ulTmp = *(pucIpMsg + ulTypeOffset + IP_ICMPV6_CODE_OFFSET);
    if(IP_IPV6_ND_VALID_CODE != ulTmp)
    {
        IPND_ERROR_LOG1(ND_TASK_PID, "IP_IsValidRAPacket: Illegal ICMPv6 CODE:!", ulTmp);
        return IP_FALSE;
    }

    return IP_TRUE;
}

/*****************************************************************************
 Function Name   : IP_GetIpv6UpLayerProtocol
 Description     : ��ȡIPv6�ϲ�Э��
 Input           : pucIpMsg---------------------IPv6���ݰ��׵�ַ
                   usPayLoad--------------------IPv6���ݰ�payload����
 Output          : pucNextHeader----------------��һͷ����ָ��
                   pulDecodedLen----------------�����볤��ָ��
 Return          : IP_ERR_ENUM_UINT32

 History         :
    1.lihong00150010      2011-03-25  Draft Enact

*****************************************************************************/
IP_ERR_ENUM_UINT32 IP_GetIpv6UpLayerProtocol
(
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT16                          usPayLoad,
    VOS_UINT8                          *pucNextHeader,
    VOS_UINT32                         *pulDecodedLen
)
{
    const VOS_UINT8                    *pucIpMsgTemp    = pucIpMsg;
    VOS_UINT8                           ucNextHeader    = IP_NULL;
    VOS_UINT8                           ucExtHeaderLen  = IP_NULL;
    VOS_UINT16                          usDecodeLen     = IP_NULL;

    IP_ASSERT_RTN(VOS_NULL_PTR != pucIpMsg, IP_FAIL);
    IP_ASSERT_RTN(VOS_NULL_PTR != pucNextHeader, IP_FAIL);
    IP_ASSERT_RTN(VOS_NULL_PTR != pulDecodedLen, IP_FAIL);

    /* ��ȡnextheader */
    ucNextHeader = *(pucIpMsgTemp + IP_IPV6_BASIC_HEAD_NEXT_HEAD_OFFSET);

    pucIpMsgTemp = pucIpMsgTemp + IP_IPV6_HEAD_LEN;

    /* �����������ݰ�����С��ulIpMsgLen */
    while (usDecodeLen <= usPayLoad)
    {
        switch (ucNextHeader)
        {
            case IP_EXTENSION_HEADER_TYPE_FRAGMENT/* �ֶ�ͷ */:
            case IP_EXTENSION_HEADER_TYPE_AH/* AHͷ */:
            case IP_EXTENSION_HEADER_TYPE_ESP/* ESPͷ */:
                *pucNextHeader = ucNextHeader;
                *pulDecodedLen = usDecodeLen + IP_IPV6_HEAD_LEN;
                return IP_SUCC;
            case IP_EXTENSION_HEADER_TYPE_HOPBYHOP/* ����ѡ��ͷ */:
            case IP_EXTENSION_HEADER_TYPE_DESTINATION/* Ŀ�ĵ�ѡ��ͷ */:
            case IP_EXTENSION_HEADER_TYPE_ROUTING/* ѡ·ͷ */:

                /* ��ǰ��չͷ�е���һ�� */
                ucNextHeader =  *(pucIpMsgTemp + IP_IPV6_EXT_HEAD_NEXT_HEAD_OFFSET);

                /* ��ȡ��չͷ�еĳ�����Ϣ����������չͷ */
                ucExtHeaderLen = *(pucIpMsgTemp + IP_IPV6_EXT_HEAD_LEN_OFFSET);

                pucIpMsgTemp = pucIpMsgTemp + IP_GetExtensionLen(ucExtHeaderLen);
                usDecodeLen = usDecodeLen + IP_GetExtensionLen(ucExtHeaderLen);

                if (usPayLoad < usDecodeLen)
                {
                    IPND_WARNING_LOG(ND_TASK_PID, "IP_GetIpv6UpLayerProtocol: Lenth Error!");
                    return IP_FAIL;
                }

                break;
            default:
                *pucNextHeader = ucNextHeader;
                *pulDecodedLen = usDecodeLen + IP_IPV6_HEAD_LEN;
                return IP_SUCC;
        }
    }

    return IP_FAIL;
}

/*****************************************************************************
 Function Name   : IP_AffirmNdParam
 Description     : ȷ��ND���Ĳ�������Ч��
 Input           : pucIpMsg ----------------  ����������ָ��
                   ulTypeOffset ------------  ICMPv6��ͷƫ����
 Output          : None
 Return          : IP_ERR_ENUM_UINT32

 History         :
    1.sunli 00180715      2011-04-12  Draft Enact

*****************************************************************************/
IP_ERR_ENUM_UINT32 IP_AffirmNdParam
(
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT32                          ulTypeOffset
)
{
    VOS_UINT32                          ulTmp           = IP_NULL;

    IP_ASSERT_RTN(VOS_NULL_PTR != pucIpMsg, PS_FALSE);

    /* Hop Limit 255 */
    ulTmp = *(pucIpMsg + IP_IPV6_BASIC_HOP_LIMIT_OFFSET);
    if(IP_IPV6_ND_HOP_LIMIT != ulTmp)
    {
        IPND_ERROR_LOG1(ND_TASK_PID, "IP_AffirmNdParam: Illegal Hop Limit:!", ulTmp);
        return IP_FAIL;
    }

    /* CODE 0 */
    ulTmp = *(pucIpMsg + ulTypeOffset + IP_ICMPV6_CODE_OFFSET);
    if(IP_IPV6_ND_VALID_CODE != ulTmp)
    {
        IPND_INFO_LOG1(ND_TASK_PID, "IP_AffirmNdParam: Illegal ICMPv6 CODE:!", ulTmp);
        return IP_FAIL;
    }

    return IP_SUCC;
}


/*****************************************************************************
 Function Name   : IP_IsIcmpv6Packet
 Description     : �ж��Ƿ�ΪICMPv6��
 Input           : pucIpMsg---------------------IP���ݰ��׵�ַ
                   ulIpMsgLen-------------------IP���ݰ�����
 Output          : pulDecodedLen----------------�����볤��ָ��
 Return          : IP_BOOL_ENUM_UINT8

 History         :
    1.lihong00150010      2011-03-25  Draft Enact

*****************************************************************************/
VOS_UINT32                          g_ulCnNd = 0;

IP_BOOL_ENUM_UINT8 IP_IsIcmpv6Packet
(
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT32                          ulIpMsgLen,
    VOS_UINT32                         *pulDecodedLen
)
{
    VOS_UINT8                           ucProtocol      = IP_NULL;
    VOS_UINT8                           ucIpVersion     = IP_NULL;
    IP_ERR_ENUM_UINT32                  ulRslt          = IP_FAIL;
    VOS_UINT32                          ulDecodedLen    = IP_NULL;
    VOS_UINT16                          usPayLoad       = IP_NULL;

    IP_ASSERT_RTN(VOS_NULL_PTR != pucIpMsg, IP_FALSE);
    IP_ASSERT_RTN(VOS_NULL_PTR != pulDecodedLen, IP_FALSE);

    /* ��ȡIP�汾�� */
    ucIpVersion = IP_GetIpVersion(pucIpMsg);

    /* ����汾�Ų���IPV6������ICMPv6�� */
    if (IP_VERSION_6 != ucIpVersion)
    {
        IPND_INFO_LOG1(ND_TASK_PID, "IP_IsIcmpv6Packet: IpVersion:", ucIpVersion);
        return IP_FALSE;
    }

    /* ��ȡPAYLOAD */
    IP_GetUint16Data(usPayLoad, pucIpMsg + IP_IPV6_BASIC_HEAD_PAYLOAD_OFFSET);

    /* ���ȺϷ���� */
    if ((VOS_UINT32)(usPayLoad + IP_IPV6_HEAD_LEN) > ulIpMsgLen)
    {
        if(1 == g_ulCnNd)
        {
            VOS_UINT32 i=0;
            PS_PRINTF("\n***********IP_IsIcmpv6Packet: %d %d***********\n", usPayLoad + IP_IPV6_HEAD_LEN, ulIpMsgLen);
            for(i=0; (i + 8) <= 1500; i = i+8)
            {
                PS_PRINTF(" %02x %02x %02x %02x %02x %02x %02x %02x\n ",
                            pucIpMsg[i], pucIpMsg[i+1],
                            pucIpMsg[i+2], pucIpMsg[i+3],
                            pucIpMsg[i+4], pucIpMsg[i+5],
                            pucIpMsg[i+6], pucIpMsg[i+7]);
            }
            while(i < 1500)
            {
                PS_PRINTF(" %02x", pucIpMsg[i++]);
            }
            PS_PRINTF("\n**********************\n\n");

        }
        IPND_WARNING_LOG2(ND_TASK_PID, "IP_IsIcmpv6Packet: PayLoad beyond the msg::!", (usPayLoad + IP_IPV6_HEAD_LEN), ulIpMsgLen);
        return IP_FALSE;
    }

    /* ��ȡ�ϲ�Э��� */
    ulRslt = IP_GetIpv6UpLayerProtocol(pucIpMsg, usPayLoad, &ucProtocol, &ulDecodedLen);
    if (IP_SUCC != ulRslt)
    {
        if(1 == g_ulCnNd)
        {
            VOS_UINT32 i=0;
            PS_PRINTF("\n***********IP_IsIcmpv6Packet: %d %d***********\n", usPayLoad + IP_IPV6_HEAD_LEN, ulIpMsgLen);
            for(i=0; (i + 8) <= 1500; i = i+8)
            {
                PS_PRINTF(" %02x %02x %02x %02x %02x %02x %02x %02x\n ",
                            pucIpMsg[i], pucIpMsg[i+1],
                            pucIpMsg[i+2], pucIpMsg[i+3],
                            pucIpMsg[i+4], pucIpMsg[i+5],
                            pucIpMsg[i+6], pucIpMsg[i+7]);
            }
            while(i < 1500)
            {
                PS_PRINTF(" %02x", pucIpMsg[i++]);
            }
            PS_PRINTF("\n**********************\n\n");

        }
        IPND_WARNING_LOG(ND_TASK_PID, "IP_IsIcmpv6Packet: Fail to get upper-layer protocol!");
        return IP_FALSE;
    }

    /* �ж��ϲ�Э����Ƿ�ΪIcmpv6 */
    if (IP_HEAD_PROTOCOL_ICMPV6 != ucProtocol)
    {
        IPND_INFO_LOG1(ND_TASK_PID, "IP_IsIcmpv6Packet: Protocol:", ucProtocol);
        return IP_FALSE;
    }

    *pulDecodedLen = ulDecodedLen;
    return IP_TRUE;
}

/*****************************************************************************
 �� �� ��  : IP_ConstructICMPv6PseudoHeader
 ��������  : Ϊ����checksum����pseudo-header
 �������  : const NAS_IP_MSG_STRU              *pstIpMsg
             VOS_UINT32                         ulTypeOffset
             IPV6_PSEDUOHEADER_STRU             *pstPseduoHeader
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��7��
    ��    ��   : 00145177
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IP_ConstructICMPv6PseudoHeader
(
    const VOS_UINT8                   *pucMsgData,
    VOS_UINT32                  ulTypeOffset,
    IPV6_PSEDUOHEADER_STRU      *pstPseduoHeader
)
{
    VOS_UINT32                          ulLength        = IP_NULL;
    VOS_UINT32                          ulLengthTmp     = IP_NULL;

    IP_ASSERT_RTN(VOS_NULL_PTR != pucMsgData, 0);
    IP_ASSERT_RTN(VOS_NULL_PTR != pstPseduoHeader, 0);

    PS_MEM_CPY(pstPseduoHeader->aucIPSrc, pucMsgData+IP_IPV6_SRC_ADDR_OFFSET, IP_IPV6_ADDR_LEN);
    PS_MEM_CPY(pstPseduoHeader->aucIPDes, pucMsgData+IP_IPV6_DST_ADDR_OFFSET, IP_IPV6_ADDR_LEN);

    pstPseduoHeader->ucNextHead = IP_HEAD_PROTOCOL_ICMPV6;

    /* ��ȡPAYLOAD */
    IP_GetUint16Data(ulLength, pucMsgData + IP_IPV6_BASIC_HEAD_PAYLOAD_OFFSET);

    ulLengthTmp = (ulTypeOffset - IP_IPV6_HEAD_LEN);
    if (ulLength > ulLengthTmp)
    {
        ulLength -= ulLengthTmp;
        IP_SetUint32Data((VOS_UINT8*)&pstPseduoHeader->ulUpperLength, ulLength);
    }
    else
    {
        ulLength = 0;
    }

    return ulLength;
}

/*****************************************************************************
 �� �� ��  : IP_Unit16Sum
 ��������  : ����16bit SUM
 �������  : VOS_UINT8 *pucData
             VOS_UINT32 ulLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��11��
    ��    ��   : 00145177
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  IP_Unit16Sum(const VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    VOS_UINT32    ulCheckSum  = 0;
    VOS_UINT16   *pBuffer;

    IP_ASSERT_RTN(VOS_NULL_PTR != pucData, 0);
    IP_ASSERT_RTN(0 != ulLen, 0);

    pBuffer = (VOS_UINT16 *)(VOS_VOID*)pucData;

    while(ulLen > 1)
    {
        ulCheckSum += *(pBuffer ++);
        ulLen      -= 2;
    }

    if (0 != ulLen)
    {
        ulCheckSum += *(VOS_UINT8*)pBuffer;
    }

    return ulCheckSum;
}

/*****************************************************************************
 �� �� ��  : IPv6_Checksum
 ��������  : ����pseduo-header��upper-layer protocal����checksum
 �������  : VOS_VOID                *pucPseduoHeader
             VOS_UINT8               *pucData
             VOS_UINT32              ulLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��7��
    ��    ��   : 00145177
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 IPv6_Checksum
(
    const VOS_VOID          *pucPseduoHeader,
    const VOS_UINT8         *pucData,
    VOS_UINT32              ulLen
)
{
    VOS_UINT32      ulCheckSum  = 0;

    IP_ASSERT_RTN(VOS_NULL_PTR != pucPseduoHeader, 0);
    IP_ASSERT_RTN(VOS_NULL_PTR != pucData, 0);
    IP_ASSERT_RTN(0 != ulLen, 0);

    /* pseduo-header��� */
    ulCheckSum += IP_Unit16Sum(pucPseduoHeader, sizeof(IPV6_PSEDUOHEADER_STRU));

    /* IPV6 Upper-layer package��� */
    ulCheckSum += IP_Unit16Sum(pucData, ulLen);

    while(ulCheckSum >> 16)
    {
        ulCheckSum  = (ulCheckSum >> 16) + (ulCheckSum & 0xffff);
    }

    return (VOS_UINT16)(~ulCheckSum);

}

/*****************************************************************************
 �� �� ��  : IP_VerifyICMPv6
 ��������  : У��checksum
 �������  : const NAS_IP_MSG_STRU              *pstIpMsg
             VOS_UINT32                         ulTypeOffset
 �������  : ��
 �� �� ֵ  : IP_ERR_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��7��
    ��    ��   : 00145177
    �޸�����   : �����ɺ���

*****************************************************************************/
IP_ERR_ENUM_UINT32 IP_VerifyICMPv6
(
    const VOS_UINT8        *pucIpMsg,
    VOS_UINT32             ulTypeOffset
)
{
    IPV6_PSEDUOHEADER_STRU  stPseduoHeader  = {{IP_NULL}};
    VOS_UINT32              ulLen;

    if ((VOS_NULL_PTR == pucIpMsg)
        || (IP_IPV6_HEAD_LEN > ulTypeOffset))
    {
        IPND_ERROR_LOG(ND_TASK_PID, "IP_VerifyICMPv6: Illegal parameter!");
        return IP_FAIL;
    }

    /* �ж��Ƿ���Ҫ���飬��û��Я��checksum����Ϊ�Ƿ������� */
    if ((0 == *(pucIpMsg + ulTypeOffset + IP_ICMPV6_CHECKSUM_OFFSET))
        && (0 == *(pucIpMsg + ulTypeOffset + IP_ICMPV6_CHECKSUM_OFFSET + 1)))
    {
        IPND_WARNING_LOG(ND_TASK_PID, "IP_VerifyICMPv6: NONE CHECKSUM!");
        return IP_FAIL;
    }

    /* ����pseduo-header */
    if (0 == (ulLen = IP_ConstructICMPv6PseudoHeader(pucIpMsg, ulTypeOffset, &stPseduoHeader)))
    {
        return IP_FAIL;
    }

    /* У��ICMPv6�� */
    if(0 != IPv6_Checksum(&stPseduoHeader, pucIpMsg + ulTypeOffset, ulLen))
    {
        IPND_WARNING_LOG(ND_TASK_PID, "IP_VerifyICMPv6: CHECKSUM Error!");
        return IP_FAIL;
    }

    return IP_SUCC;
}

/*****************************************************************************
 �� �� ��  : IP_IsValidNdMsg
 ��������  : ����Ƿ��ǺϷ���ND package
 �������  : const NAS_IP_MSG_STRU              *pstIpMsg
             VOS_UINT32                         *pulTypeOffset
 �������  : ��
 �� �� ֵ  : IP_BOOL_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��7��
    ��    ��   : 00145177
    �޸�����   : �����ɺ���

*****************************************************************************/
IP_BOOL_ENUM_UINT8 IP_IsValidNdMsg
(
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT32                          ulIpMsgLen,
    VOS_UINT32                         *pulTypeOffset
)
{
    VOS_UINT32                          ulDecodedLen    = IP_NULL;
    VOS_UINT8                           ucType          = IP_NULL;

    IP_ASSERT_RTN(VOS_NULL_PTR != pucIpMsg, IP_FALSE);
    IP_ASSERT_RTN(VOS_NULL_PTR != pulTypeOffset, IP_FALSE);

    /* �ж��Ƿ�ΪICMPv6�� */
    if (IP_TRUE != IP_IsIcmpv6Packet(pucIpMsg, ulIpMsgLen, &ulDecodedLen))
    {
        IPND_ERROR_LOG(ND_TASK_PID, "IP_IsValidNdMsg: Not Icmpv6 Packet");
        return IP_FALSE;
    }

    if (IP_SUCC != IP_VerifyICMPv6(pucIpMsg, ulDecodedLen))
    {
        IPND_ERROR_LOG(ND_TASK_PID, "IP_IsValidNdMsg: Verify Fail");
        return IP_FALSE;
    }

    /* ȡICMPV6��Ϣ�е�TYPE�ֶ� */
    ucType = *(pucIpMsg + ulDecodedLen);
    if (IP_ICMPV6_TYPE_ECHOREQUEST != ucType)
    {
        if (IP_SUCC != IP_AffirmNdParam(pucIpMsg, ulDecodedLen))
        {
            IPND_ERROR_LOG(ND_TASK_PID, "IP_IsValidNdMsg: ND Param Affirm Fail");
            return IP_FALSE;
        }
    }

    /* TYPE�Ƿ�λ��[128,137] */
    if ((IP_ICMPV6_TYPE_ECHOREQUEST <= ucType)
        && (IP_ICMPV6_TYPE_REDIRECT >= ucType))
    {
        *pulTypeOffset = ulDecodedLen;
        return IP_TRUE;
    }

    IPND_ERROR_LOG1(ND_TASK_PID, "IP_IsValidNdMsg: Invalid ICMPv6 Msg:!", ucType);

    return IP_FALSE;
}

/*****************************************************************************
 Function Name   : IP_BuildIcmpv6Checksum
 Description     : ����ICMPv6��ͷ��У���
 Input           : pucIpMsg ----------------  ����������ָ��
                   ulTypeOffset ------------  ICMPv6��ͷƫ����
 Output          : pucIpMsg ----------------  ��������ICMPv6��ͷλ�����У���
 Return          : IP_ERR_ENUM_UINT32

 History         :
    1.sunli 00180715      2011-04-12  Draft Enact

*****************************************************************************/
IP_ERR_ENUM_UINT32 IP_BuildIcmpv6Checksum
(
    VOS_UINT8                          *pucIpMsg,
    VOS_UINT32                          ulTypeOffset
)
{
    IPV6_PSEDUOHEADER_STRU              stPseduoHeader = {{IP_NULL}};
    VOS_UINT32                          ulLen          = IP_NULL;
    VOS_UINT16                          usCheckSum     = IP_NULL;

    if ((VOS_NULL_PTR == pucIpMsg)
        || (IP_IPV6_HEAD_LEN > ulTypeOffset))
    {
        IPND_ERROR_LOG(ND_TASK_PID, "IP_BuildICMPv6Checksum: Illegal parameter!\n");
        return IP_FAIL;
    }

    /* ���ICMPv6У����ֶ� */
    pucIpMsg[ulTypeOffset + IP_ICMPV6_CHECKSUM_OFFSET] = 0;
    pucIpMsg[ulTypeOffset + IP_ICMPV6_CHECKSUM_OFFSET + 1] = 0;

    /* ����pseduo-header */
    if (0 == (ulLen = IP_ConstructICMPv6PseudoHeader(pucIpMsg, ulTypeOffset, &stPseduoHeader)))
    {
        return IP_FAIL;
    }

    /* ����ICMPv6��У��� */
    usCheckSum = IPv6_Checksum(&stPseduoHeader, pucIpMsg + ulTypeOffset, ulLen);

    /*IP_SetUint16Data(&pucIpMsg[ulTypeOffset + IP_ICMPV6_CHECKSUM_OFFSET], usCheckSum);*/
    *(VOS_UINT16 *)(VOS_VOID*)(&pucIpMsg[ulTypeOffset + IP_ICMPV6_CHECKSUM_OFFSET]) = usCheckSum;

    return IP_SUCC;
}


/*huibo from V3R1 begin*/
/*****************************************************************************
 �� �� ��  : TTF_NDIS_IP6_Checksum_Update
 ��������  :
 �������  : pbuf   -- �������IP��������ָ��
             ulBytes -- ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��19��
    ��    ��   : Hefeng 163499
    �޸�����   :
*****************************************************************************/
VOS_UINT32  TTF_NDIS_IP6_Checksum_Update(void *pbuf, VOS_UINT32 ulBytes)
{
    VOS_UINT32    ulSum;
    VOS_UINT32    ulNwords;
    VOS_UINT16   *buf;


    buf = (VOS_UINT16 *) pbuf;
    ulSum = 0;

    for (ulNwords = (VOS_UINT32)ulBytes >> 5; ulNwords > 0; ulNwords--)
    {
        ulSum += *buf++; ulSum += *buf++; ulSum += *buf++; ulSum += *buf++;
        ulSum += *buf++; ulSum += *buf++; ulSum += *buf++; ulSum += *buf++;
        ulSum += *buf++; ulSum += *buf++; ulSum += *buf++; ulSum += *buf++;
        ulSum += *buf++; ulSum += *buf++; ulSum += *buf++; ulSum += *buf++;
    }
    for (ulNwords = (VOS_UINT32)(ulBytes & 0x1f) >> 1; ulNwords > 0; ulNwords--)
    {
        ulSum += *buf++;
    }

    /* Add left-over byte, if any. */
    if (ulBytes & 0x01)
    {
        /*lint -e778*/
        ulSum += *buf & VOS_HTONS(0xff00);
        /*lint +e778*/
    }

    return ulSum;
}

/*****************************************************************************
 �� �� ��  : TTF_NDIS_IP6_Pseudo_Header_Checksum_Update
 ��������  :
 �������  : pstIp6SrcAddr - The source address.
              pstIp6DstAddr - The destination address.
              ulProto       - The protcol ID of the upper layer protocol.
              usLen         - The number of octets in the payload for which this is
                    pseudo header.
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��19��
    ��    ��   : Hefeng 163499
    �޸�����   :
*****************************************************************************/
VOS_UINT32  TTF_NDIS_IP6_Pseudo_Header_Checksum_Update
(
    const NDIS_IP6_ADDR_STRU                 *pstIp6SrcAddr,
    const NDIS_IP6_ADDR_STRU                 *pstIp6DstAddr,
    VOS_UINT32                          ulProto,
    VOS_UINT16                          usLen
)
{
    VOS_UINT32                          ulSum;

    ulSum  = pstIp6SrcAddr->in6.ausAddr[0];
    ulSum += pstIp6SrcAddr->in6.ausAddr[1];
    ulSum += pstIp6SrcAddr->in6.ausAddr[2];
    ulSum += pstIp6SrcAddr->in6.ausAddr[3];
    ulSum += pstIp6SrcAddr->in6.ausAddr[4];
    ulSum += pstIp6SrcAddr->in6.ausAddr[5];
    ulSum += pstIp6SrcAddr->in6.ausAddr[6];
    ulSum += pstIp6SrcAddr->in6.ausAddr[7];

    ulSum += pstIp6DstAddr->in6.ausAddr[0];
    ulSum += pstIp6DstAddr->in6.ausAddr[1];
    ulSum += pstIp6DstAddr->in6.ausAddr[2];
    ulSum += pstIp6DstAddr->in6.ausAddr[3];
    ulSum += pstIp6DstAddr->in6.ausAddr[4];
    ulSum += pstIp6DstAddr->in6.ausAddr[5];
    ulSum += pstIp6DstAddr->in6.ausAddr[6];
    ulSum += pstIp6DstAddr->in6.ausAddr[7];

    ulSum += VOS_HTONS(usLen);
    ulSum += VOS_HTONS(ulProto);

    return ulSum;
}

/*****************************************************************************
 �� �� ��  : TTF_NDIS_IP6_Checksum_Finish
 ��������  :
 �������  : ulSum - The accumulated 32 bit internet sum.
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��19��
    ��    ��   : Hefeng 163499
    �޸�����   :
*****************************************************************************/
VOS_UINT16  TTF_NDIS_IP6_Checksum_Finish(VOS_UINT32 ulSum)
{
    /* Fold 32-bit sum to 16 bits. */
    while (ulSum >> 16)
    {
        ulSum = (ulSum & 0xffff) + (ulSum >> 16);
    }

    return (VOS_UINT16)~(VOS_UINT16)ulSum;
}


/*****************************************************************************
 �� �� ��  : TTF_NDIS_Ipv6_CalcCheckSum
 ��������  : ����IP����CheckSum
 �������  : pData         -  IPv6����
              usLen         -  IPv6�����ܳ���
              pstDstIP6Addr - Ŀ��IPv6��ַ
              pstSrcIP6Addr - ԴIPv6��ַ
              ulProto       - IPv6��������
 �������  : ��
 �� �� ֵ  : VOS_UINT16 - CheckSumֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��24��
    ��    ��   : Hefeng 163499
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 TTF_NDIS_Ipv6_CalcCheckSum
(
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen,
    const NDIS_IP6_ADDR_STRU           *pstIp6SrcAddr,
    const NDIS_IP6_ADDR_STRU           *pstIp6DstAddr,
    VOS_UINT32                          ulProto
)
{
    VOS_UINT32                          ulCheckSum;
    VOS_UINT32                          ulPseudoHdrChksum;
    VOS_UINT32                          ulFinalChksum;
    VOS_UINT16                          usStdIntelChksum;


    ulCheckSum          = TTF_NDIS_IP6_Checksum_Update(pData, usLen);
    ulPseudoHdrChksum   = TTF_NDIS_IP6_Pseudo_Header_Checksum_Update(pstIp6SrcAddr,
                                                    pstIp6DstAddr, ulProto, usLen);
    ulFinalChksum       = ulCheckSum + ulPseudoHdrChksum;
    usStdIntelChksum    = TTF_NDIS_IP6_Checksum_Finish(ulFinalChksum);

    return usStdIntelChksum;
}

/*****************************************************************************
 �� �� ��  : TTF_NDIS_Ipv6GetDhcpOption
 ��������  : Returns a specific option.
 �������  : pFirstOpt - Points to the first option in the packet.
             ulTotOptLen - Length in byte of ICMPv6 header + data.
             usNdOptCode - The option Code to find.
             lNumber - The number of the option (if the same option can occure
              multiple times).
 �������  : pOpt - Will point to the option when the function returns,
              or to VOS_NULL_PTR if the option was not found.
 �� �� ֵ  :PS_SUCC - �ɹ�
             PS_FAIL - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��28��
    ��    ��   : �Ʒ� 62119
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TTF_NDIS_Ipv6GetDhcpOption
(
    IPV6_PKT_DHCP_OPT_HDR_STRU             *pFirstOpt,
    VOS_UINT16                              usTotOptLen,
    VOS_UINT16                              usNdOptCode,
    IPV6_PKT_DHCP_OPT_HDR_STRU            **pOpt,
    VOS_INT32                               lNumber
)
{
    VOS_UINT16                          usOptLen;


    *pOpt = pFirstOpt;

    while ( usTotOptLen > 0 )
    {
        usOptLen = VOS_NTOHS((*pOpt)->usDhcpOptLen);
        if ( usOptLen == 0 )
        {
            return PS_FAIL;
        }

        if ( VOS_NTOHS((*pOpt)->usDhcpOptCode) == usNdOptCode )
        {
            if (  lNumber == 0  )
            {
                return PS_SUCC;
            }

            lNumber--;
        }

        usTotOptLen    -= usOptLen ;
        *pOpt           = (IPV6_PKT_DHCP_OPT_HDR_STRU *)(VOS_VOID*)(((VOS_UINT8 *) *pOpt + usOptLen) + 4 );
    }

    *pOpt = VOS_NULL_PTR;


    return PS_SUCC;
}

/*****************************************************************************
 �� �� ��  : TTF_NDIS_Ipv6InputEthHead
 ��������  : ���IPͷ��
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��28��
    ��    ��   : Hefeng 163499
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TTF_NDIS_InputUDPHead
(
    VOS_UINT8                          *pBuf,
    VOS_UINT16                          usSrcPort,
    VOS_UINT16                          usDstPort,
    VOS_UINT16                          usUdpDataLen
)
{
    UDP_HEAD_ST        *pstUdpHdr = (UDP_HEAD_ST*)(VOS_VOID*)pBuf;

    if ( usUdpDataLen < sizeof(UDP_HEAD_ST) )
    {
        return VOS_ERR;
    }

    PS_MEM_SET(pstUdpHdr, 0, sizeof(UDP_HEAD_ST));
    pstUdpHdr->usSrcPort    = VOS_HTONS(usSrcPort);
    pstUdpHdr->usDstPort    = VOS_HTONS(usDstPort);
    pstUdpHdr->usLen        = VOS_HTONS(usUdpDataLen);
    pstUdpHdr->usCheck      = 0;

    return VOS_OK;
}


