




/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "vos.h"
/*#include "PsTypeDef.h"
 */
#include "PsNdis.h"
#include "Ipv4DhcpServer.h"
#include "IpComm.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_IPV4DHCPSERVER_C
/*lint +e767*/


/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
extern VOS_UINT8                g_aucBroadCastAddr[];
extern NDIS_ENTITY_STRU         g_astNdisEntity[];

/*���IPV4ʵ��*/
#define IPV4_DHCP_GET_NDIS_ENTITY(Index)        (&g_astNdisEntity[(Index)])

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*������DHCP OFFER/ACK/NACKʱ����ʱ������*/
VOS_UINT8     g_aucDhcpBuff[ETH_MAX_FRAME_SIZE] = {0};
/*define global DHCP Server stat info struct*/
IPV4_DHCP_STAT_INFO_STRU   g_stDhcpStatStru = {0};
/*define IP Layer Identity*/
VOS_UINT16    g_usIpHdrIdentity   = 0;
/*define DHCP Adddr Lease Time*/
VOS_UINT32    g_ulLeaseTime = (60*60*24*3);
/*define DHCP Packet Magic Cookie; it's the IP Addr : 99.130.83.99*/
VOS_UINT8     g_aucMagicCookie[] = {0x63,0x82,0x53,0x63};

/*define MACRO to access global var*/
#define  IP_GET_IP_IDENTITY()          (g_usIpHdrIdentity ++)
#define  IPV4_DHCP_GET_BUFFER()        (g_aucDhcpBuff)

/*****************************************************************************
  3 Function
*****************************************************************************/
extern VOS_UINT32 Ndis_SendMacFrm(const VOS_UINT8  *pucBuf, VOS_UINT32 ulLen, VOS_UINT8 ucRabId);
/*****************************************************************************
 Function Name   : IP_CalcCRC16
 Description     : ����CRC 16У���
 Input           : VOS_UINT8 *pucData : crc src buf
                   VOS_UINT16 usLen : src buf len
 Output          :
 Return          : the crc16 result of Src buf
                   (PS: the result is network byte order)

 History         :
    1.y00151394      2011-3-7  Draft Enact

*****************************************************************************/
VOS_UINT16  IP_CalcCRC16(VOS_UINT8 *pucData, VOS_UINT16 usLen)
{
    VOS_UINT32    ulCheckSum  = 0;
    VOS_UINT16   *pBuffer;


    IP_NDIS_ASSERT_RTN(VOS_NULL_PTR != pucData,0);

    if (0 == usLen)
    {
        return 0;
    }

    pBuffer = (VOS_UINT16 *)((VOS_VOID*)pucData);

    while(usLen > 1)
    {
        ulCheckSum += *(pBuffer ++);
        usLen      -= sizeof(VOS_UINT16);
    }

    if (0 != usLen)
    {
        ulCheckSum += *(VOS_UINT8*)pBuffer;
    }

    ulCheckSum  = (ulCheckSum >> 16) + (ulCheckSum & 0xffff);
    ulCheckSum += (ulCheckSum >> 16);

    return (VOS_UINT16)(~ulCheckSum);

}

/*****************************************************************************
 Function Name   : IPV4_DHCP_SendDhcpToEth
 Description     : ��DHCP����װ��Ethnet֡���͵�Ethnet��
 Input           :
 Output          :
 Return          :

 History         :
    1.y00151394      2011-3-7  Draft Enact

*****************************************************************************/
VOS_VOID IPV4_DHCP_SendDhcpToEth(const IPV4_DHCP_ANALYSE_RESULT_STRU *pstDhcpAnalyse,
                                           const NDIS_IPV4_INFO_STRU           *pstIpV4Entity,
                                           VOS_UINT16                           usDhcpLen,
                                           VOS_UINT8                            ucRabId)
{
    ETH_IPFIXHDR_STRU            *pstIPFixHdr;
    IPV4_UDPIPFAKEHDR_STRU       *pstUdpIpFakeHdr;
    VOS_UINT16                    usCheckSum;
    VOS_UINT16                    usCurTotalLen;
    VOS_UINT16                    usUdpCrcLen;
    VOS_UINT32                    ulDstIp  = 0xffffffff;

    if ((VOS_NULL_PTR == pstDhcpAnalyse) || (VOS_NULL_PTR == pstIpV4Entity))
    {
        IP_ERROR_LOG("IPV4_DHCP_SendDhcpToEth : Input Para Error");
        return;
    }

    if (IPV4_DHCP_OPTION_OFFSET >= usDhcpLen)
    {
        IP_ERROR_LOG1("IPV4_DHCP_SendDhcpToEth : Input Len too Small ",usDhcpLen);
        return;
    }

    /*unicast*/
    if (IP_CAST_TYPE_UNICAST == pstDhcpAnalyse->usCastFlg)
    {
        ulDstIp = pstDhcpAnalyse->unSrcIPAddr.ulIpAddr;
    }

    /*UDP*/
    /*UDPIP Fake Hdr Offset, Same to IP Hdr Offset*/
    pstUdpIpFakeHdr = (IPV4_UDPIPFAKEHDR_STRU *)(IPV4_DHCP_GET_BUFFER() + ETH_MAC_HEADER_LEN );
    /*Fill Fake Hdr*/
    IP_MEM_SET(pstUdpIpFakeHdr->aucRec0,0,sizeof(pstUdpIpFakeHdr->aucRec0));
    pstUdpIpFakeHdr->unSrcIP.ulIpAddr = pstIpV4Entity->unGwIpInfo.ulIpAddr;
    pstUdpIpFakeHdr->unDstIP.ulIpAddr = ulDstIp;
    pstUdpIpFakeHdr->ucProtocol = IP_PROTOCOL_UDP;
    pstUdpIpFakeHdr->ucAll0     = 0;
    pstUdpIpFakeHdr->usLength   = IP_HTONS(usDhcpLen + IP_UDP_HDR_LEN);
    /*Fill Udp Hdr*/
    pstUdpIpFakeHdr->usSrcPort = UDP_DHCP_SERVICE_PORT;
    pstUdpIpFakeHdr->usDstPort = UDP_DHCP_CLIENT_PORT;
    pstUdpIpFakeHdr->usChecksum = 0;
    pstUdpIpFakeHdr->usLen = pstUdpIpFakeHdr->usLength;

    usCurTotalLen = usDhcpLen + IP_UDP_HDR_LEN;

    /*Calc UDP CRC16*/
    usUdpCrcLen = usCurTotalLen + IPV4_FIX_HDR_LEN;
    usCheckSum = IP_CalcCRC16((VOS_UINT8 *)pstUdpIpFakeHdr, usUdpCrcLen);
    if (0 == usCheckSum)
    {
        usCheckSum = 0xFFFF;
    }
    pstUdpIpFakeHdr->usChecksum = usCheckSum;

    /*IP*/
    pstIPFixHdr = (ETH_IPFIXHDR_STRU*)(IPV4_DHCP_GET_BUFFER() + ETH_MAC_HEADER_LEN );
    /*Fill IP Fix Header*/
    pstIPFixHdr->ucIpHdrLen = IPV4_FIX_HDR_LEN >> 2;
    pstIPFixHdr->ucIpVer    = IP_IPV4_VERSION;
    pstIPFixHdr->ucServiceType = 0;
    pstIPFixHdr->usTotalLen   = IP_HTONS(usCurTotalLen + IPV4_FIX_HDR_LEN);
    pstIPFixHdr->usIdentification = IP_GET_IP_IDENTITY();
    pstIPFixHdr->usIdentification = IP_HTONS(pstIPFixHdr->usIdentification);
    pstIPFixHdr->usOffset     = 0;
    pstIPFixHdr->ucTTL        = IPV4_HDR_TTL;
    pstIPFixHdr->ucProtocol   = IP_PROTOCOL_UDP;
    pstIPFixHdr->usCheckSum   = 0;
    pstIPFixHdr->ulSrcAddr = pstIpV4Entity->unGwIpInfo.ulIpAddr;
    pstIPFixHdr->ulDestAddr= ulDstIp;

    /*IP HDR CRC16*/
    pstIPFixHdr->usCheckSum = IP_CalcCRC16((VOS_UINT8*)pstIPFixHdr,IPV4_FIX_HDR_LEN);

    usCurTotalLen = usCurTotalLen + IPV4_FIX_HDR_LEN;

    /*MAC*/
    IP_MEM_CPY(IPV4_DHCP_GET_BUFFER(),pstIpV4Entity->aucMacFrmHdr,ETH_MAC_HEADER_LEN);
    /*Update Dst Mac Addr */
    if (IP_CAST_TYPE_UNICAST == pstDhcpAnalyse->usCastFlg)
    {
        IP_MEM_CPY(IPV4_DHCP_GET_BUFFER(),pstIpV4Entity->aucUeMacAddr,ETH_MAC_ADDR_LEN);
    }
    else
    {
        IP_MEM_CPY(IPV4_DHCP_GET_BUFFER(),g_aucBroadCastAddr,ETH_MAC_ADDR_LEN);
    }

    usCurTotalLen += ETH_MAC_HEADER_LEN;

    if (PS_SUCC != Ndis_SendMacFrm(IPV4_DHCP_GET_BUFFER(),usCurTotalLen,ucRabId))
    {
        IP_ERROR_LOG("IPV4_DHCP_SendDhcpToEth:Send Dhcp Packet Error");
        IPV4_DHCP_STAT_SEND_PKT_FAIL(1);
    }
    else
    {
        IPV4_DHCP_STAT_SEND_PKT_SUCC(1);
    }


    return;
}

/*****************************************************************************
 Function Name   : IPV4_DHCP_FormDhcpHdrStru
 Description     : form dhcp packet fix header
 Input           : VOS_UINT8 *pucDhcpData : �����߱�֤���ȴ���DHCP�̶�ͷ����
 Output          :
 Return          :

 History         :
    1.y00151394      2011-3-7  Draft Enact

*****************************************************************************/
VOS_VOID IPV4_DHCP_FormDhcpHdrStru(const IPV4_DHCP_ANALYSE_RESULT_STRU *pstDhcpAnalyse,VOS_UINT8 *pucDhcpData)
{
    IPV4_DHCP_PROTOCL_STRU    *pstDhcpHdr;

    if ((VOS_NULL_PTR == pucDhcpData) || (VOS_NULL_PTR == pstDhcpAnalyse))
    {
        IP_ERROR_LOG("IPV4_DHCP_FormDhcpHdrStru : Input Para NULL");
        return;
    }

    pstDhcpHdr = (IPV4_DHCP_PROTOCL_STRU*)((VOS_VOID*)pucDhcpData);

    pstDhcpHdr->ucOP = IPV4_DHCP_OPERATION_REPLY;
    pstDhcpHdr->ucHardwareType = IPV4_DHCP_ETHERNET_HTYPE;
    pstDhcpHdr->ucHardwareLength = ETH_MAC_ADDR_LEN;
    pstDhcpHdr->ucHops = 0;
    pstDhcpHdr->ulTransactionID = pstDhcpAnalyse->ulTransactionID;
    pstDhcpHdr->usSeconds = 0;
    pstDhcpHdr->usFlags = 0;
    pstDhcpHdr->unClientIPAddr.ulIpAddr = 0;
    pstDhcpHdr->unRelayIPAddr.ulIpAddr  = 0;
    pstDhcpHdr->unNextServerIPAddr.ulIpAddr = 0;
    IP_MEM_CPY(pstDhcpHdr->aucClientHardwardAddr,pstDhcpAnalyse->aucHardwareAddr,ETH_MAC_ADDR_LEN);

    /*Magic Cookie*/
    IP_MEM_CPY(pstDhcpHdr->aucMagicCookie,g_aucMagicCookie,sizeof(g_aucMagicCookie));

    return;
}


/*****************************************************************************
 Function Name   : IPV4_DHCP_FormOption
 Description     : ����Optionѡ��
 Input           :
 Output          : pusOptionLen : formed option len
 Return          :

 History         :
    1.y00151394      2011-3-7  Draft Enact

*****************************************************************************/
VOS_VOID IPV4_DHCP_FormOption(const NDIS_IPV4_INFO_STRU *pstIpV4Entity,
                                      VOS_UINT8               *pucOption,
                                      VOS_UINT8                ucDhcpType,
                                      VOS_UINT16              *pusOptionLen)

{
    IPV4_DHCP_OPTION_ITEM_STRU  *pstOptionItem;
    VOS_UINT8                    ucDnsLen;
    VOS_UINT32                   ulTimeLen;
    VOS_UINT8                   *pucOptionAddr;
    VOS_UINT8                    ucWinsLen;

    if ((VOS_NULL_PTR == pstIpV4Entity) || (VOS_NULL_PTR == pucOption)
        || (VOS_NULL_PTR == pusOptionLen))
    {
        IP_ERROR_LOG("IPV4_DHCP_FormOption : Input Para Is NULL");
        return;
    }

    pucOptionAddr = pucOption;
    /* �������� */
    pstOptionItem = (IPV4_DHCP_OPTION_ITEM_STRU *)((VOS_VOID*)pucOptionAddr);
    pstOptionItem->ucOptionType = IPV4_DHCP_OPTION_MSG_TYPE;
    pstOptionItem->ucOptionLen  = 1;
    pstOptionItem->aucOptionValue[0] = ucDhcpType;
    *pusOptionLen += 3;
    pucOptionAddr += 3;

    /* �������� */
    pstOptionItem = (IPV4_DHCP_OPTION_ITEM_STRU *)((VOS_VOID*)pucOptionAddr);
    pstOptionItem->ucOptionType = IPV4_DHCP_OPTION_SUBNET_MASK;
    pstOptionItem->ucOptionLen  = IPV4_ADDR_LEN;
    IP_MEM_CPY(pstOptionItem->aucOptionValue,&(pstIpV4Entity->unNmIpInfo),IPV4_ADDR_LEN);
    *pusOptionLen += IPV4_ADDR_LEN + 2;
    pucOptionAddr += IPV4_ADDR_LEN + 2;

    /* Ĭ������ */
    pstOptionItem = (IPV4_DHCP_OPTION_ITEM_STRU *)((VOS_VOID*)pucOptionAddr);
    pstOptionItem->ucOptionType = IPV4_DHCP_OPTION_ROUTER_IP;
    pstOptionItem->ucOptionLen  = IPV4_ADDR_LEN;
    IP_MEM_CPY(pstOptionItem->aucOptionValue,&(pstIpV4Entity->unGwIpInfo),IPV4_ADDR_LEN);
    *pusOptionLen += IPV4_ADDR_LEN + 2;
    pucOptionAddr += IPV4_ADDR_LEN + 2;

    /* DNS */
    ucDnsLen = 0;
    pstOptionItem = (IPV4_DHCP_OPTION_ITEM_STRU *)((VOS_VOID*)pucOptionAddr);
    pstOptionItem->ucOptionType = IPV4_DHCP_OPTION_DOMAIN_NAME_SERVER;
    if (0 != pstIpV4Entity->unPrimDnsAddr.ulIpAddr)
    {
        IP_MEM_CPY(pstOptionItem->aucOptionValue,&(pstIpV4Entity->unPrimDnsAddr),IPV4_ADDR_LEN);
        ucDnsLen += IPV4_ADDR_LEN;
    }

    if (0 != pstIpV4Entity->unSecDnsAddr.ulIpAddr)
    {
        IP_MEM_CPY(pstOptionItem->aucOptionValue + ucDnsLen,&(pstIpV4Entity->unSecDnsAddr),IPV4_ADDR_LEN);
        ucDnsLen += IPV4_ADDR_LEN;
    }

    pstOptionItem->ucOptionLen  = ucDnsLen;
    if (0 != ucDnsLen)
    {
        *pusOptionLen += ucDnsLen + 2;
        pucOptionAddr += ucDnsLen + 2;
    }

    /* DHCP SERVER IP */
    pstOptionItem = (IPV4_DHCP_OPTION_ITEM_STRU *)((VOS_VOID*)pucOptionAddr);
    pstOptionItem->ucOptionType = IPV4_DHCP_OPTION_SERVER_IP;
    pstOptionItem->ucOptionLen  = IPV4_ADDR_LEN;
    IP_MEM_CPY(pstOptionItem->aucOptionValue,&(pstIpV4Entity->unGwIpInfo),IPV4_ADDR_LEN);
    *pusOptionLen += IPV4_ADDR_LEN + 2;
    pucOptionAddr += IPV4_ADDR_LEN + 2;

    /*  ���� */
    pstOptionItem = (IPV4_DHCP_OPTION_ITEM_STRU *)((VOS_VOID*)pucOptionAddr);
    pstOptionItem->ucOptionType = IPV4_DHCP_OPTION_LEASE_TIME;
    pstOptionItem->ucOptionLen  = IPV4_DHCP_OPTION_LEASE_TIME_LEN;
    /* ת��Ϊ�����ֽ��� */
    ulTimeLen = IPV4_DHCP_LEASE_TIME;
    ulTimeLen = IP_HTONL(ulTimeLen);
    IP_MEM_CPY(pstOptionItem->aucOptionValue,&ulTimeLen,IPV4_DHCP_OPTION_LEASE_TIME_LEN);
    *pusOptionLen += IPV4_DHCP_OPTION_LEASE_TIME_LEN + 2;
    pucOptionAddr += IPV4_DHCP_OPTION_LEASE_TIME_LEN + 2;

    /* Renewal (T1) Time Value */
    pstOptionItem = (IPV4_DHCP_OPTION_ITEM_STRU *)((VOS_VOID*)pucOptionAddr);
    pstOptionItem->ucOptionType = IPV4_DHCP_OPTION_T1;
    pstOptionItem->ucOptionLen  = IPV4_DHCP_OPTION_LEASE_TIME_LEN;
    ulTimeLen = (VOS_UINT32)IPV4_DHCP_T1;
    ulTimeLen = IP_HTONL(ulTimeLen);
    IP_MEM_CPY(pstOptionItem->aucOptionValue,&ulTimeLen,IPV4_DHCP_OPTION_LEASE_TIME_LEN);
    *pusOptionLen += IPV4_DHCP_OPTION_LEASE_TIME_LEN + 2;
    pucOptionAddr += IPV4_DHCP_OPTION_LEASE_TIME_LEN + 2;

    /* Renewal (T2) Time Value */
    pstOptionItem = (IPV4_DHCP_OPTION_ITEM_STRU *)((VOS_VOID*)pucOptionAddr);
    pstOptionItem->ucOptionType = IPV4_DHCP_OPTION_T2;
    pstOptionItem->ucOptionLen  = IPV4_DHCP_OPTION_LEASE_TIME_LEN;
    ulTimeLen = (VOS_UINT32)IPV4_DHCP_T2;
    ulTimeLen = IP_HTONL(ulTimeLen);
    IP_MEM_CPY(pstOptionItem->aucOptionValue,&ulTimeLen,IPV4_DHCP_OPTION_LEASE_TIME_LEN);
    *pusOptionLen += IPV4_DHCP_OPTION_LEASE_TIME_LEN + 2;
    pucOptionAddr += IPV4_DHCP_OPTION_LEASE_TIME_LEN + 2;

    /*WINS : NetBios Name Server*/
    ucWinsLen = 0;
    pstOptionItem = (IPV4_DHCP_OPTION_ITEM_STRU *)((VOS_VOID*)pucOptionAddr);
    pstOptionItem->ucOptionType = IPV4_DHCP_OPTION_NETBIOS_NAME_SERVER;
    if (0 != pstIpV4Entity->unPrimWinsAddr.ulIpAddr)
    {
        IP_MEM_CPY(pstOptionItem->aucOptionValue,&(pstIpV4Entity->unPrimWinsAddr),IPV4_ADDR_LEN);
        ucWinsLen += IPV4_ADDR_LEN;
    }

    if (0 != pstIpV4Entity->unSecWinsAddr.ulIpAddr)
    {
        IP_MEM_CPY(pstOptionItem->aucOptionValue + ucWinsLen,&(pstIpV4Entity->unSecWinsAddr),IPV4_ADDR_LEN);
        ucWinsLen += IPV4_ADDR_LEN;
    }

    pstOptionItem->ucOptionLen  = ucWinsLen;
    if (0 != ucWinsLen)
    {
        *pusOptionLen += ucWinsLen + 2;
        pucOptionAddr += ucWinsLen + 2;
    }

    /*  End Option 0xff option������־*/
    *pucOptionAddr = 0xFF;
    *pusOptionLen += 1;

    return;

}

/*****************************************************************************
 Function Name   : IPV4_DHCP_FormOfferMsg
 Description     : ����DHCP OFFER��Ϣ��
 Input           :
 Output          :
 Return          : �ɹ�����PS_SUCC;ʧ�ܷ���PS_FAIL

 History         :
    1.y00151394      2011-3-7  Draft Enact

*****************************************************************************/
VOS_UINT32 IPV4_DHCP_FormOfferMsg(const IPV4_DHCP_ANALYSE_RESULT_STRU *pstDhcpAnalyse,
                                         const NDIS_IPV4_INFO_STRU     *pstIpV4Entity,
                                         VOS_UINT16                    *pusLen)
{
    VOS_UINT8           *pucDhcpPktBuf;
    VOS_UINT32           ulDhcpOffset;
    VOS_UINT16           usDhcpOptionLen = 0;

    if ((VOS_NULL_PTR == pstDhcpAnalyse)||(VOS_NULL_PTR == pstIpV4Entity)||(VOS_NULL_PTR == pusLen))
    {
        IP_ERROR_LOG("IPV4_DHCP_FormOfferMsg : Input Para NULL");
        return PS_FAIL;
    }

    /*��BUF �� ��*/
    VOS_MemSet(IPV4_DHCP_GET_BUFFER(), 0, ETH_MAX_FRAME_SIZE);

    ulDhcpOffset = ETH_MAC_HEADER_LEN + IPV4_FIX_HDR_LEN + IP_UDP_HDR_LEN;
    pucDhcpPktBuf = IPV4_DHCP_GET_BUFFER() + ulDhcpOffset;

    IPV4_DHCP_FormDhcpHdrStru(pstDhcpAnalyse,pucDhcpPktBuf);

    /* ����your ip address */
    IP_MEM_CPY(pucDhcpPktBuf + IPV4_DHCP_HEAD_YIADDR_OFFSET, \
               pstIpV4Entity->unUeIpInfo.aucIPAddr, IPV4_ADDR_LEN);

    /* dhcp option ���� */
    pucDhcpPktBuf += IPV4_DHCP_OPTION_OFFSET;
    IPV4_DHCP_FormOption(pstIpV4Entity,pucDhcpPktBuf, \
                         IPV4_DHCP_MSG_OFFER, &usDhcpOptionLen);

    /* ����д��ĳ��� */
    *pusLen = usDhcpOptionLen + IPV4_DHCP_OPTION_OFFSET;

    return PS_SUCC;
}

/*****************************************************************************
 Function Name   : IPV4_DHCP_FormAckMsg
 Description     : ����DHCP ACK��Ϣ
 Input           :
 Output          :
 Return          :

 History         :
    1.y00151394      2011-3-7  Draft Enact

*****************************************************************************/
VOS_VOID IPV4_DHCP_FormAckMsg(const IPV4_DHCP_ANALYSE_RESULT_STRU *pstDhcpAnalyse,
                                        const NDIS_IPV4_INFO_STRU           *pstIpV4Entity,
                                        VOS_UINT16                          *pusLen)
{

    VOS_UINT8           *pucDhcpPktBuf;
    VOS_UINT32           ulDhcpOffset;
    VOS_UINT16           usDhcpOptionLen = 0;

    IP_NDIS_ASSERT(VOS_NULL_PTR != pstDhcpAnalyse);
    IP_NDIS_ASSERT(VOS_NULL_PTR != pstIpV4Entity);
    IP_NDIS_ASSERT(VOS_NULL_PTR != pusLen);

    /*��BUF �� ��*/
    VOS_MemSet(IPV4_DHCP_GET_BUFFER(), 0, ETH_MAX_FRAME_SIZE);
    ulDhcpOffset = ETH_MAC_HEADER_LEN + IPV4_FIX_HDR_LEN + IP_UDP_HDR_LEN;
    pucDhcpPktBuf = IPV4_DHCP_GET_BUFFER() + ulDhcpOffset;

    /* ����DHCP����ͷ�й̶����� */
    IPV4_DHCP_FormDhcpHdrStru(pstDhcpAnalyse,pucDhcpPktBuf);

    /* ����your ip address */
    IP_MEM_CPY(pucDhcpPktBuf + IPV4_DHCP_HEAD_YIADDR_OFFSET, \
               pstIpV4Entity->unUeIpInfo.aucIPAddr, IPV4_ADDR_LEN);

    /*Form Option */
    pucDhcpPktBuf += IPV4_DHCP_OPTION_OFFSET;
    IPV4_DHCP_FormOption(pstIpV4Entity,pucDhcpPktBuf, \
                         IPV4_DHCP_MSG_ACK, &usDhcpOptionLen);

    /* ����д��ĳ��� */
    *pusLen = usDhcpOptionLen + IPV4_DHCP_OPTION_OFFSET;

    return;
}

/*****************************************************************************
 Function Name   : IPV4_DHCP_FormNakMsg
 Description     : ����DHCP NACK��Ϣ
 Input           :
 Output          :
 Return          :

 History         :
    1.y00151394      2011-3-7  Draft Enact

*****************************************************************************/
VOS_VOID IPV4_DHCP_FormNackMsg(const IPV4_DHCP_ANALYSE_RESULT_STRU *pstDhcpAnalyse,
                                        const NDIS_IPV4_INFO_STRU       *pstIpV4Entity,
                                        VOS_UINT16                      *pusLen)
{
    VOS_UINT8                     *pucDhcpPktBuf;
    VOS_UINT32                     ulDhcpOffset;
    VOS_UINT16                     usDhcpOptionLen;
    IPV4_DHCP_OPTION_ITEM_STRU    *pstOptionItem;

    if ((VOS_NULL_PTR == pstDhcpAnalyse)||(VOS_NULL_PTR == pstIpV4Entity)||(VOS_NULL_PTR == pusLen))
    {
        IP_ERROR_LOG("IPV4_DHCP_FormNackMsg : Input Para NULL");
        return ;
    }

    /*��BUF �� ��*/
    VOS_MemSet(IPV4_DHCP_GET_BUFFER(), 0, ETH_MAX_FRAME_SIZE);
    ulDhcpOffset = ETH_MAC_HEADER_LEN + IPV4_FIX_HDR_LEN + IP_UDP_HDR_LEN;
    pucDhcpPktBuf = IPV4_DHCP_GET_BUFFER() + ulDhcpOffset;

    /* Fill Dhcp Fix Hdr,and Keep your ip address to 0*/
    IPV4_DHCP_FormDhcpHdrStru(pstDhcpAnalyse,pucDhcpPktBuf);

    /*Form NACK Option*/
    usDhcpOptionLen = 0;
    pucDhcpPktBuf += IPV4_DHCP_OPTION_OFFSET;

    /* DHCP Msg Type*/
    pstOptionItem = (IPV4_DHCP_OPTION_ITEM_STRU *)(pucDhcpPktBuf);
    pstOptionItem->ucOptionType = IPV4_DHCP_OPTION_MSG_TYPE;
    pstOptionItem->ucOptionLen  = 1;
    pstOptionItem->aucOptionValue[0] = IPV4_DHCP_MSG_NAK;
    usDhcpOptionLen   += 3;
    pucDhcpPktBuf     += 3;

    /* DHCP SERVER IP */
    pstOptionItem = (IPV4_DHCP_OPTION_ITEM_STRU *)pucDhcpPktBuf;
    pstOptionItem->ucOptionType = IPV4_DHCP_OPTION_SERVER_IP;
    pstOptionItem->ucOptionLen  = IPV4_ADDR_LEN;
    IP_MEM_CPY(pstOptionItem->aucOptionValue,&(pstIpV4Entity->unGwIpInfo),IPV4_ADDR_LEN);
    usDhcpOptionLen   += IPV4_ADDR_LEN + 2;
    pucDhcpPktBuf     += IPV4_ADDR_LEN + 2;

    /*  End Option 0xff option������־*/
    *pucDhcpPktBuf   = 0xFF;
    usDhcpOptionLen += 1;

    /* ����д��ĳ��� */
    *pusLen = usDhcpOptionLen + IPV4_DHCP_OPTION_OFFSET;


    return;
}

/*****************************************************************************
 Function Name   : IPV4_DHCP_FindIPV4Entity
 Description     : ����DHCP Client MAC Addr������Ӧ��IPV4ʵ��;
                   �ɵ����߱�֤���ExRabId��Ӧһ��NDISʵ��
 Input           : VOS_UINT8 ucRabId
 Output          :
 Return          : NDIS_IPV4_INFO_STRU

 History         :
    1.y00151394      2011-3-7  Draft Enact
    2.h00159435      2011-12-9
    3.h00218138      2013-1-16  DSDA
*****************************************************************************/
NDIS_IPV4_INFO_STRU * IPV4_DHCP_FindIPV4Entity(VOS_UINT8 ucExRabId)
{
    NDIS_ENTITY_STRU         *pstNdisEntity;
    NDIS_IPV4_INFO_STRU      *pstIpv4Info;

    /*�ɵ����߱�֤���ExRabId��Ӧһ��NDISʵ��*/
    pstNdisEntity = NDIS_GetEntityByRabId(ucExRabId);
    if(VOS_NULL_PTR == pstNdisEntity)
    {
        return VOS_NULL_PTR;
    }
    pstIpv4Info   = &(pstNdisEntity->stIpV4Info);

    return pstIpv4Info;
}

/*****************************************************************************
 Function Name   : IPV4_DHCP_DiscoverMsgProc
 Description     : ����DHCP DISCOVER��Ϣ
 Input           :
 Output          :
 Return          :

 History         :
    1.y00151394      2011-3-7  Draft Enact

*****************************************************************************/
VOS_VOID IPV4_DHCP_DiscoverMsgProc(IPV4_DHCP_ANALYSE_RESULT_STRU *pstDhcpAnalyse, VOS_UINT8 ucRabId)
{

    NDIS_IPV4_INFO_STRU      *pstIpV4Entity;
    VOS_UINT16                usDhcpLength;

    if (VOS_NULL_PTR == pstDhcpAnalyse)
    {
        IP_ERROR_LOG("IPV4_DHCP_DiscoverMsgProc : Input Para pstDhcpAnalyse is NULL");
        return;
    }

    /*find the dhcp sever entity by ue mac*/
    pstIpV4Entity = IPV4_DHCP_FindIPV4Entity(ucRabId);
    if (VOS_NULL_PTR == pstIpV4Entity)
    {
        IP_ERROR_LOG("IPV4_DHCP_DiscoverMsgProc : Not Available IPV4 Entity");
        IPV4_DHCP_STAT_PROC_ERR(1);
        return;
    }

    pstDhcpAnalyse->usCastFlg = IP_CAST_TYPE_BRODCAST;

    /*form dhcp offer msg*/
    usDhcpLength = 0;
    if (PS_SUCC != IPV4_DHCP_FormOfferMsg(pstDhcpAnalyse,pstIpV4Entity,&usDhcpLength))
    {
        IP_ERROR_LOG("IPV4_DHCP_DiscoverMsgProc : Form Offer Msg Fail");
        IPV4_DHCP_STAT_PROC_ERR(1);
        return;
    }

    /*send dhcp pkt to ethnet*/
    IPV4_DHCP_SendDhcpToEth(pstDhcpAnalyse,pstIpV4Entity,usDhcpLength, ucRabId);
    IPV4_DHCP_STAT_SEND_OFFER(1);

    return;
}
/*****************************************************************************
 Function Name   : IPV4_DHCP_SelectingRequestMsgProc
 Description     : ����Selecting״̬�µ�������Ϣ
 Input           :
 Output          :
 Return          :

 History         :
    1.y00151394      2011-3-7  Draft Enact

*****************************************************************************/
VOS_VOID IPV4_DHCP_SelectingRequestMsgProc(const IPV4_DHCP_ANALYSE_RESULT_STRU *pstDhcpAnalyse,
                                                       NDIS_IPV4_INFO_STRU       *pstIpV4Entity,
                                                       VOS_UINT8  ucRabId)
{
    VOS_UINT16    usDhcpAckLen = 0;

    if ((VOS_NULL_PTR == pstDhcpAnalyse) || (VOS_NULL_PTR == pstIpV4Entity))
    {
        IP_ERROR_LOG("IPV4_DHCP_SelectingRequestMsgProc : Input Para is NULL");
        return;
    }

    /*�жϵ�ǰ��Ϣ*/
    if ((pstDhcpAnalyse->unServerIPAddr.ulIpAddr == pstIpV4Entity->unGwIpInfo.ulIpAddr)
         &&(pstDhcpAnalyse->unRequestIPAddr.ulIpAddr == pstIpV4Entity->unUeIpInfo.ulIpAddr))
    {

        /*����DHCP ACK������*/
        IPV4_DHCP_FormAckMsg(pstDhcpAnalyse,pstIpV4Entity,&usDhcpAckLen);
        IPV4_DHCP_SendDhcpToEth(pstDhcpAnalyse,pstIpV4Entity,usDhcpAckLen,ucRabId);

        IPV4_DHCP_STAT_SEND_ACK(1);

        /*����IP��ַΪ�ѷ���*/
        pstIpV4Entity->ulIpAssignStatus = IPV4_DHCP_ADDR_STATUS_ASSIGNED;
    }
    else
    {
        /*δѡ�� DHCP Server,����IP��ַδ����*/
        pstIpV4Entity->ulIpAssignStatus = IPV4_DHCP_ADDR_STATUS_FREE;
        IP_ERROR_LOG("IPV4_DHCP_SelectingRequestMsgProc : The Client Has not Select Local IP");
    }

    return;
}

/*****************************************************************************
 Function Name   : IPV4_DHCP_OtherRequestMsgProc
 Description     : �����Selecting״̬�µ�������Ϣ
 Input           :
 Output          :
 Return          :

 History         :
    1.y00151394      2011-3-7  Draft Enact

*****************************************************************************/
VOS_VOID IPV4_DHCP_OtherRequestMsgProc( const IPV4_DHCP_ANALYSE_RESULT_STRU *pstDhcpAnalyse,
                                                   const NDIS_IPV4_INFO_STRU    *pstIpV4Entity,
                                                   VOS_UINT8  ucRabId)
{
    VOS_UINT16    usDhcpAckLen = 0;

    if ((VOS_NULL_PTR == pstDhcpAnalyse) || (VOS_NULL_PTR == pstIpV4Entity))
    {
        IP_ERROR_LOG("IPV4_DHCP_OtherRequestMsgProc : Input Para is NULL");
        return;
    }


    /*������IPͬUE IP��ͬ�����ACK;����ظ�NACK*/
    if (pstDhcpAnalyse->unClientIPAddr.ulIpAddr == pstIpV4Entity->unUeIpInfo.ulIpAddr)
    {
        IPV4_DHCP_FormAckMsg(pstDhcpAnalyse,pstIpV4Entity,&usDhcpAckLen);
        IPV4_DHCP_SendDhcpToEth(pstDhcpAnalyse,pstIpV4Entity,usDhcpAckLen,ucRabId);
        IPV4_DHCP_STAT_SEND_ACK(1);
    }
    else
    {

        IPV4_DHCP_FormNackMsg(pstDhcpAnalyse,pstIpV4Entity,&usDhcpAckLen);
        IPV4_DHCP_SendDhcpToEth(pstDhcpAnalyse,pstIpV4Entity,usDhcpAckLen,ucRabId);
        /*NACK ERROR LOG*/
        IP_ERROR_LOG("IPV4_DHCP_OtherRequestMsgProc : The Client Renew/Rebinding Request Fail");
        IPV4_DHCP_STAT_SEND_NACK(1);
    }

    return;
}

/*****************************************************************************
 Function Name   : IPV4_DHCP_InitRebootRequestProc
 Description     : ����Client ��Init-Reboot״̬�µ�������Ϣ
 Input           :
 Output          :
 Return          :

 History         :
    1.y00151394      2011-3-7  Draft Enact

*****************************************************************************/
VOS_VOID IPV4_DHCP_InitRebootRequestProc( const IPV4_DHCP_ANALYSE_RESULT_STRU *pstDhcpAnalyse,
                                                    NDIS_IPV4_INFO_STRU    *pstIpV4Entity,
                                                    VOS_UINT8  ucRabId)
{
    VOS_UINT16    usDhcpAckLen = 0;

    if ((VOS_NULL_PTR == pstDhcpAnalyse) || (VOS_NULL_PTR == pstIpV4Entity))
    {
        IP_ERROR_LOG("IPV4_DHCP_InitRebootRequestProc : Input Para is NULL");
        return;
    }

    /*������IPͬUE IP��ͬ�����ACK;����ظ�NACK*/
    if (pstDhcpAnalyse->unRequestIPAddr.ulIpAddr == pstIpV4Entity->unUeIpInfo.ulIpAddr)
    {
        IPV4_DHCP_FormAckMsg(pstDhcpAnalyse,pstIpV4Entity,&usDhcpAckLen);
        IPV4_DHCP_SendDhcpToEth(pstDhcpAnalyse,pstIpV4Entity,usDhcpAckLen,ucRabId);
        pstIpV4Entity->ulIpAssignStatus = IPV4_DHCP_ADDR_STATUS_ASSIGNED;
        IPV4_DHCP_STAT_SEND_ACK(1);
    }
    else
    {

        IPV4_DHCP_FormNackMsg(pstDhcpAnalyse,pstIpV4Entity,&usDhcpAckLen);
        IPV4_DHCP_SendDhcpToEth(pstDhcpAnalyse,pstIpV4Entity,usDhcpAckLen,ucRabId);
        /*NACK ERROR LOG*/
        IP_ERROR_LOG("IPV4_DHCP_InitRebootRequestProc : The Init-Reboot Client Request IP Fail");
        IPV4_DHCP_STAT_SEND_NACK(1);
    }

    return;
}

/*****************************************************************************
 Function Name   : IPV4_DHCP_RequestMsgProc
 Description     : ����DHCP REQUEST��Ϣ
 Input           :
 Output          :
 Return          :

 History         :
    1.y00151394      2011-3-7  Draft Enact

*****************************************************************************/
VOS_VOID IPV4_DHCP_RequestMsgProc(IPV4_DHCP_ANALYSE_RESULT_STRU *pstDhcpAnalyse, VOS_UINT8 ucRabId)
{
    NDIS_IPV4_INFO_STRU      *pstIpV4Entity;

    if (VOS_NULL_PTR == pstDhcpAnalyse)
    {
        IP_ERROR_LOG("IPV4_DHCP_RequestMsgProc : Input Para NULL");
        return;
    }

    pstIpV4Entity = IPV4_DHCP_FindIPV4Entity(ucRabId);
    if (VOS_NULL_PTR == pstIpV4Entity)
    {
        IP_ERROR_LOG("IPV4_DHCP_RequestMsgProc : Not Available IPV4 Entity");
        IPV4_DHCP_STAT_PROC_ERR(1);
        return;
    }

    /*

     Client messages from different states
     ---------------------------------------------------------------------
     |              |INIT-REBOOT  |SELECTING    |RENEWING     |REBINDING |
     ---------------------------------------------------------------------
     |broad/unicast |broadcast    |broadcast    |unicast      |broadcast |
     |server-ip     |MUST NOT     |MUST         |MUST NOT     |MUST NOT  |
     |requested-ip  |MUST         |MUST         |MUST NOT     |MUST NOT  |
     |ciaddr        |zero         |zero         |IP address   |IP address|
     ---------------------------------------------------------------------

     */
    if (0 != pstDhcpAnalyse->unServerIPAddr.ulIpAddr)
    {
        /*Selecting Request*/
        pstDhcpAnalyse->usCastFlg = IP_CAST_TYPE_BRODCAST;
        IPV4_DHCP_SelectingRequestMsgProc(pstDhcpAnalyse,pstIpV4Entity,ucRabId);
    }
    else if (0 == pstDhcpAnalyse->unClientIPAddr.ulIpAddr)
    {
        /*INIT-REBOOT Request*/
        pstDhcpAnalyse->usCastFlg = IP_CAST_TYPE_BRODCAST;
        IPV4_DHCP_InitRebootRequestProc(pstDhcpAnalyse,pstIpV4Entity,ucRabId);
    }
    else
    {
        /*renew or rebinding*/
        pstDhcpAnalyse->usCastFlg = IP_CAST_TYPE_UNICAST;
        IPV4_DHCP_OtherRequestMsgProc(pstDhcpAnalyse, pstIpV4Entity,ucRabId);
    }

    return;
}

/*****************************************************************************
 Function Name   : IPV4_DHCP_ReleaseMsgProc
 Description     : ����DHCP RELEASE��Ϣ
 Input           :
 Output          :
 Return          :

 History         :
    1.y00151394      2011-3-7  Draft Enact

*****************************************************************************/
VOS_VOID IPV4_DHCP_ReleaseMsgProc(const IPV4_DHCP_ANALYSE_RESULT_STRU *pstDhcpAnalyse, VOS_UINT8 ucRabId)
{
    NDIS_IPV4_INFO_STRU      *pstIpV4Entity;

    if (VOS_NULL_PTR == pstDhcpAnalyse)
    {
        IP_ERROR_LOG("IPV4_DHCP_ReleaseMsgProc : Input Para pstDhcpAnalyse is NULL");
        return;
    }

    pstIpV4Entity = IPV4_DHCP_FindIPV4Entity(ucRabId);
    if (VOS_NULL_PTR == pstIpV4Entity)
    {
        IP_ERROR_LOG("IPV4_DHCP_DiscoverMsgProc : Not Available IPV4 Entity");
        IPV4_DHCP_STAT_PROC_ERR(1);
        return;
    }

    /*�޸ķ���״̬ : δ����*/
    pstIpV4Entity->ulIpAssignStatus = IPV4_DHCP_ADDR_STATUS_FREE;
    /*Other Operation : FFS*/

    return;
}

/*****************************************************************************
 Function Name   : IPV4_DHCP_ProcDhcpMsg
 Description     : ����DHCP���ݱ�
 Input           :
 Output          :
 Return          : VOS_VOID

 History         :
    1.y00151394      2011-3-7  Draft Enact

*****************************************************************************/
VOS_VOID IPV4_DHCP_ProcDhcpMsg(IPV4_DHCP_ANALYSE_RESULT_STRU *pstDhcpAnalyse, VOS_UINT8 ucRabId)
{
    NDIS_IPV4_INFO_STRU             *pstIpV4Entity;

    if (VOS_NULL_PTR == pstDhcpAnalyse)
    {
        IP_ERROR_LOG("IPV4_DHCP_ProcDhcpMsg : Input Para pstDhcpAnalyse is NULL");
        return;
    }

    /*find the dhcp sever entity by ue mac*/
    pstIpV4Entity = IPV4_DHCP_FindIPV4Entity(ucRabId);
    if (VOS_NULL_PTR == pstIpV4Entity)
    {
        IP_ERROR_LOG("IPV4_DHCP_ProcDhcpMsg : Not Available IPV4 Entity");
        IPV4_DHCP_STAT_PROC_ERR(1);
        return;
    }

    /* save the ue mac addr,and update the mac hdr*/
    IP_MEM_CPY(pstIpV4Entity->aucUeMacAddr,pstDhcpAnalyse->aucHardwareAddr,ETH_MAC_ADDR_LEN);
    IP_MEM_CPY(pstIpV4Entity->aucMacFrmHdr,pstDhcpAnalyse->aucHardwareAddr,ETH_MAC_ADDR_LEN);
    pstIpV4Entity->ulArpInitFlg = PS_TRUE;

    switch (pstDhcpAnalyse->enMsgType)
    {
        case IPV4_DHCP_MSG_DISCOVER:
            IPV4_DHCP_DiscoverMsgProc(pstDhcpAnalyse, ucRabId);
            IPV4_DHCP_STAT_RECV_DISCOVER_MSG(1);
            break;

        case IPV4_DHCP_MSG_REQUEST:
            IPV4_DHCP_RequestMsgProc(pstDhcpAnalyse, ucRabId);
            IPV4_DHCP_STAT_RECV_REQUEST_MSG(1);
            break;

        case IPV4_DHCP_MSG_RELEASE:
            IPV4_DHCP_ReleaseMsgProc(pstDhcpAnalyse, ucRabId);
            IPV4_DHCP_STAT_RECV_RELEASE_MSG(1);
            break;

        case IPV4_DHCP_MSG_DECLINE:
            /* ����DECLINE������ */
            IP_ERROR_LOG("IP_DHCPV4SERVER_ProcRabmDataInd:DECLINE Msg is received!");
            IPV4_DHCP_STAT_RECV_OTHER_TYPE_MSG(1);
            break;

        case IPV4_DHCP_MSG_INFORM:
            /* ����INFORM������ */
            IP_ERROR_LOG("IP_DHCPV4SERVER_ProcRabmDataInd:INFORM Msg is received!");
            IPV4_DHCP_STAT_RECV_OTHER_TYPE_MSG(1);
            break;

        default :
            IP_ERROR_LOG("IP_DHCPV4SERVER_ProcRabmDataInd:Illegal DHCPV4 Msg!");
            IPV4_DHCP_STAT_RECV_OTHER_TYPE_MSG(1);
            break;
    }

    return;
}

/*****************************************************************************
 Function Name   : IPV4_DHCP_AnalyseDhcpPkt
 Description     : ����DHCP����
 Input           :
 Output          : IPV4_DHCP_ANALYSE_RESULT_STRU *pstAnalyseRst : DHCP���Ľ������
 Return          :

 History         :
    1.y00151394      2011-3-7  Draft Enact

*****************************************************************************/
VOS_VOID IPV4_DHCP_AnalyseDhcpPkt( VOS_UINT8                     *pucDhcp,
                                            VOS_UINT32                     ulDhcpLen,
                                            IPV4_DHCP_ANALYSE_RESULT_STRU *pstAnalyseRst)
{
    IPV4_DHCP_PROTOCL_STRU        *pstDhcpFixHdr;
    VOS_UINT8                     *pucOptionStart;
    VOS_UINT8                     *pucOptionEnd;
    IPV4_DHCP_OPTION_ITEM_STRU    *pstOptionStru;

    if ((VOS_NULL_PTR == pucDhcp)||(VOS_NULL_PTR == pstAnalyseRst))
    {
        IP_ERROR_LOG("IPV4_DHCP_AnalyseDhcpPkt : Input Para is NULL");
        return;
    }

    if (IPV4_DHCP_OPTION_OFFSET > ulDhcpLen)
    {
        IP_ERROR_LOG1("IPV4_DHCP_AnalyseDhcpPkt : Dhcp Packet is small ",ulDhcpLen);
        return;
    }

    /*��¼DHCP�̶�ͷ�е���Ϣ*/
    pstDhcpFixHdr = (IPV4_DHCP_PROTOCL_STRU *)((VOS_VOID*)pucDhcp);
    pstAnalyseRst->ulTransactionID = pstDhcpFixHdr->ulTransactionID;
    pstAnalyseRst->unClientIPAddr.ulIpAddr = pstDhcpFixHdr->unClientIPAddr.ulIpAddr;
    pstAnalyseRst->unYourIPAddr.ulIpAddr   = pstDhcpFixHdr->unYourIPAddr.ulIpAddr;
    pstAnalyseRst->ucHardwareLen = ETH_MAC_ADDR_LEN;
    IP_MEM_CPY(pstAnalyseRst->aucHardwareAddr,pstDhcpFixHdr->aucClientHardwardAddr,ETH_MAC_ADDR_LEN);

    /*Option Start and End Address,not include Magic Code*/
    pucOptionStart = pucDhcp + IPV4_DHCP_OPTION_OFFSET;
    /*Remove End */
    pucOptionEnd   = pucOptionStart + ulDhcpLen -  IPV4_DHCP_OPTION_OFFSET;

    while (pucOptionStart < pucOptionEnd )
    {
        pstOptionStru = (IPV4_DHCP_OPTION_ITEM_STRU *)((VOS_VOID*)pucOptionStart);

        if (IPV4_DHCP_OPTION_MSG_TYPE == pstOptionStru->ucOptionType)
        {
            IP_MEM_CPY(&(pstAnalyseRst->enMsgType),pstOptionStru->aucOptionValue,IPV4_DHCP_OPTION_MSG_TYPE_LEN);
        }
        else if (IPV4_DHCP_OPTION_REQUEST_IP_ADDR == pstOptionStru->ucOptionType)
        {
            IP_MEM_CPY(&(pstAnalyseRst->unRequestIPAddr),pstOptionStru->aucOptionValue,IPV4_ADDR_LEN);
        }
        else if (IPV4_DHCP_OPTION_SERVER_IP == pstOptionStru->ucOptionType)
        {
            IP_MEM_CPY(&(pstAnalyseRst->unServerIPAddr),pstOptionStru->aucOptionValue,IPV4_ADDR_LEN);
        }
        else if (IPV4_DHCP_OPTION_PAD_OPTIOIN == pstOptionStru->ucOptionType)
        {
            /*PAD Only 1 byte*/
            pucOptionStart ++;
            continue;
        }
        else if (IPV4_DHCP_OPTION_END_OPTION == pstOptionStru->ucOptionType)
        {
            break;
        }
        else
        {
        }

        pucOptionStart += pstOptionStru->ucOptionLen + IP_DHCPV4_OPTION_ITEM_HDR_LEN;

    }

    return ;
}

/*****************************************************************************
 Function Name   : IPV4_DHCP_DhcpPktIPInfoCheck
 Description     : DHCP����IP����Ϣ���
 Input           : VOS_UINT8  *pucIpPkt ָ��IPͷ��ʼ��λ��
 Output          :
 Return          : VOS_VOID

 History         :
    1.y00151394      2011-3-7  Draft Enact
*****************************************************************************/
VOS_UINT32 IPV4_DHCP_DhcpPktIPInfoCheck(VOS_UINT8  *pucIpPkt, VOS_UINT32  ulIpMemLen)
{
    ETH_IPFIXHDR_STRU       *pstIpHdr;
    VOS_UINT32               ulIpHdrLen;
    VOS_UINT32               ulIpLen;

    /*IPͷ�ڴ����*/
    if (sizeof(ETH_IPFIXHDR_STRU) > ulIpMemLen)
    {
        return PS_FALSE;
    }

    pstIpHdr = (ETH_IPFIXHDR_STRU *)((VOS_VOID*)pucIpPkt);
    ulIpHdrLen = pstIpHdr->ucIpHdrLen << 2;
    ulIpLen = IP_NTOHS(pstIpHdr->usTotalLen);

    /*��IPv4���ݰ�*/
    if (IP_IPV4_VERSION != pstIpHdr->ucIpVer)
    {
        return PS_FALSE;
    }

    /*��UDP��*/
    if (IP_PROTOCOL_UDP != pstIpHdr->ucProtocol)
    {
        return PS_FALSE;
    }

    /*IPͷ�г��ȺϷ����ж�*/
    if ((ulIpLen > ulIpMemLen) || (ulIpHdrLen >= ulIpMemLen) || (ulIpHdrLen >= ulIpLen))
    {
        return PS_FALSE;
    }

    /*����UDPͷ*/
    if ((ulIpHdrLen + IP_UDP_HDR_LEN) > ulIpMemLen)
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 Function Name   : IPV4_DHCP_DhcpPktUdpInfoCheck
 Description     : DHCP����UDP��Ϣ���
 Input           : VOS_UINT8  *pucIpPkt ָ��UDPͷ��ʼ��λ��
 Output          :
 Return          : VOS_VOID

 History         :
    1.y00151394      2011-3-7  Draft Enact
*****************************************************************************/
VOS_UINT32 IPV4_DHCP_DhcpPktUdpInfoCheck(VOS_UINT8  *pucUdp, VOS_UINT32  ulUdpMemLen)
{
    ETH_UDPHDR_STRU         *pstUdpHdr;
    VOS_UINT32               ulUdpLen;

    /*ͷ�����ж�*/
    if (IP_UDP_HDR_LEN > ulUdpMemLen)
    {
        return PS_FALSE;
    }

    /*UDP���ȺϷ���*/
    pstUdpHdr = (ETH_UDPHDR_STRU *)((VOS_VOID*)pucUdp);
    ulUdpLen  = IP_NTOHS(pstUdpHdr->usLen);
    if (ulUdpLen > ulUdpMemLen)
    {
        return PS_FALSE;
    }

    /*�˿ں�67*/
    if (UDP_DHCP_SERVICE_PORT != pstUdpHdr->usDstPort)
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 Function Name   : IPV4_DHCP_DhcpPktDhcpInfoCheck
 Description     : DHCP����UDP��Ϣ���
 Input           : VOS_UINT8  *pucIpPkt ָ��UDPͷ��ʼ��λ��
 Output          :
 Return          : VOS_VOID

 History         :
    1.y00151394      2011-3-7  Draft Enact
*****************************************************************************/
VOS_UINT32 IPV4_DHCP_DhcpPktDhcpInfoCheck(VOS_UINT8  *pucDhcp, VOS_UINT32  ulDhcpMemLen)
{
    IPV4_DHCP_PROTOCL_STRU      *pstDhcpFixHdr;
    IPV4_DHCP_OPTION_ITEM_STRU  *pstOptionStru;
    VOS_UINT8                   *pucOptionStart;
    VOS_UINT8                   *pucOptionEnd;

    /*DHCP�̶�ͷ����*/
    if (sizeof(IPV4_DHCP_PROTOCL_STRU) > ulDhcpMemLen)
    {
        return PS_FALSE;
    }

    /*��ַ���ȷǷ�*/
    pstDhcpFixHdr = (IPV4_DHCP_PROTOCL_STRU *)((VOS_VOID*)pucDhcp);
    if (pstDhcpFixHdr->ucHardwareLength > ETH_MAC_ADDR_LEN)
    {
        return PS_FALSE;
    }

    /*OPTION�ж�*/
    pucOptionStart = pucDhcp + sizeof(IPV4_DHCP_PROTOCL_STRU);
    pucOptionEnd   = pucOptionStart + (ulDhcpMemLen - sizeof(IPV4_DHCP_PROTOCL_STRU));
    while (pucOptionStart < pucOptionEnd )
    {
        pstOptionStru = (IPV4_DHCP_OPTION_ITEM_STRU *)((VOS_VOID*)pucOptionStart);
        if (IPV4_DHCP_OPTION_PAD_OPTIOIN == pstOptionStru->ucOptionType)
        {
            /*PAD Only 1 byte*/
            pucOptionStart ++;
        }
        else if (IPV4_DHCP_OPTION_END_OPTION == pstOptionStru->ucOptionType)
        {
            break;
        }
        else
        {
            /*�ж�OptionLen�Ƿ���Ч*/
            if ((pucOptionStart + IP_DHCPV4_OPTION_ITEM_HDR_LEN) > pucOptionEnd)
            {
                return PS_FALSE;
            }

            pucOptionStart += pstOptionStru->ucOptionLen + IP_DHCPV4_OPTION_ITEM_HDR_LEN;
        }
    }

    if (pucOptionStart > pucOptionEnd)
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


/*****************************************************************************
 Function Name   : IPV4_DHCP_IsDhcpPacket
 Description     : �ж��Ƿ���DHCP����
 Input           : VOS_UINT8  *pucIpPkt ָ��IPͷ��ʼ��λ��
 Output          :
 Return          : VOS_VOID

 History         :
    1.y00151394      2011-3-7  Draft Enact
*****************************************************************************/
VOS_UINT32 IPV4_DHCP_IsDhcpPacket(VOS_UINT8  *pucIpPkt, VOS_UINT32  ulPktMemLen)
{
    ETH_IPFIXHDR_STRU       *pstIpHdr;
    VOS_UINT32               ulIpHdrLen;
    VOS_UINT8               *pucUdp;
    VOS_UINT32               ulUdpMemLen;
    VOS_UINT8               *pucDhcp;
    VOS_UINT32               ulDhcpMemLen;

    if (VOS_NULL_PTR == pucIpPkt)
    {
        return PS_FALSE;
    }

    /*IP���ж�*/
    if (PS_TRUE != IPV4_DHCP_DhcpPktIPInfoCheck(pucIpPkt,ulPktMemLen))
    {
        return PS_FALSE;
    }

    /*UDP�ж�*/
    pstIpHdr    = (ETH_IPFIXHDR_STRU *)((VOS_VOID*)pucIpPkt);
    ulIpHdrLen  = pstIpHdr->ucIpHdrLen << 2;
    pucUdp      = pucIpPkt + ulIpHdrLen;
    ulUdpMemLen = ulPktMemLen - ulIpHdrLen;
    if (PS_TRUE != IPV4_DHCP_DhcpPktUdpInfoCheck(pucUdp, ulUdpMemLen))
    {
        return PS_FALSE;
    }

    /*DHCP�ж�*/
    pucDhcp      = pucUdp + IP_UDP_HDR_LEN;
    ulDhcpMemLen = ulUdpMemLen - IP_UDP_HDR_LEN;
    if (PS_TRUE != IPV4_DHCP_DhcpPktDhcpInfoCheck(pucDhcp,ulDhcpMemLen))
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}



/*****************************************************************************
 Function Name   : IPV4_DHCP_ProcDhcpPkt
 Description     : ����DHCP����
 Input           : VOS_UINT8  *pucIpPkt ָ��IPͷ��ʼ��λ��
 Output          :
 Return          : VOS_VOID

 History         :
    1.y00151394      2011-3-7  Draft Enact

*****************************************************************************/
VOS_VOID IPV4_DHCP_ProcDhcpPkt(VOS_UINT8  *pucIpPkt, VOS_UINT8 ucRabId, VOS_UINT32 ulPktMemLen)
{
    IPV4_DHCP_ANALYSE_RESULT_STRU    stDhcpRst;
    ETH_IPFIXHDR_STRU               *pstIpFixHdr;
    VOS_UINT32                       ulDhcpOffset;
    VOS_UINT32                       ulDhcpLen;

    if (VOS_NULL_PTR == pucIpPkt)
    {
        IP_ERROR_LOG("IPV4_DHCP_ProcDhcpPkt : Input Para Is NULL");
        return;
    }

    /*not dhcp packet*/
    if (PS_TRUE != IPV4_DHCP_IsDhcpPacket(pucIpPkt,ulPktMemLen))
    {
        return;
    }

    /*record src ip and dst ip in the ip hdr */
    IP_MEM_SET(&stDhcpRst,0,sizeof(IPV4_DHCP_ANALYSE_RESULT_STRU));
    pstIpFixHdr = (ETH_IPFIXHDR_STRU *)((VOS_VOID*)pucIpPkt);
    stDhcpRst.unSrcIPAddr.ulIpAddr = pstIpFixHdr->ulSrcAddr;
    stDhcpRst.unDstIpAddr.ulIpAddr = pstIpFixHdr->ulDestAddr;

    /*analyse the dhcp packet*/
    ulDhcpOffset = (pstIpFixHdr->ucIpHdrLen << 2) + IP_UDP_HDR_LEN;
    ulDhcpLen = ulPktMemLen - ulDhcpOffset;

    if (ETH_MAX_FRAME_SIZE <= ulDhcpLen)
    {
        IP_ERROR_LOG1("IPV4_DHCP_ProcDhcpPkt : Dhcp Len Error,Len : ",ulDhcpLen);
        return;
    }

    IPV4_DHCP_AnalyseDhcpPkt(pucIpPkt + ulDhcpOffset, ulDhcpLen, &stDhcpRst);

    /* proc analysis dhcp packet result */
    IPV4_DHCP_ProcDhcpMsg(&stDhcpRst, ucRabId);

    IPV4_DHCP_STAT_RECV_DHCP_PKT(1);

    return;
}

/*****************************************************************************
 Function Name   : IPV4_DHCP_ShowDebugInfo
 Description     : ��ӡDHCP Server������Ϣ
 Input           :
 Output          :
 Return          : VOS_VOID

 History         :
    1.y00151394      2011-3-7  Draft Enact

*****************************************************************************/
VOS_VOID IPV4_DHCP_ShowDebugInfo(VOS_VOID)
{
    PS_PRINTF("Recv Dhcp Packet              :    %d \r\n",g_stDhcpStatStru.ulRecvDhcpPkt);
    PS_PRINTF("Recv Dhcp Discover  Msg       :    %d \r\n",g_stDhcpStatStru.ulRecvDiscoverMsg);
    PS_PRINTF("Recv Dhcp Request   Msg       :    %d \r\n",g_stDhcpStatStru.ulRecvRequestMsg);
    PS_PRINTF("Recv Dhcp Selecting Msg       :    %d \r\n",g_stDhcpStatStru.ulRecvSelectingReqMsg);
    PS_PRINTF("Recv Dhcp Other     Msg       :    %d \r\n",g_stDhcpStatStru.ulRecvOtherReqMsg);
    PS_PRINTF("Recv Dhcp Release   Msg       :    %d \r\n",g_stDhcpStatStru.ulRecvReleaseMsg);
    PS_PRINTF("Recv Dhcp Other Typ Msg       :    %d \r\n",g_stDhcpStatStru.ulRecvOtherTypeMsg);
    PS_PRINTF("Proc Dhcp Packet    Error     :    %d \r\n",g_stDhcpStatStru.ulProcErr);
    PS_PRINTF("Send Dhcp Offer               :    %d \r\n",g_stDhcpStatStru.ulSendOffer);
    PS_PRINTF("Send Dhcp Ack                 :    %d \r\n",g_stDhcpStatStru.ulSendAck);
    PS_PRINTF("Send Dhcp NACK                :    %d \r\n",g_stDhcpStatStru.ulSendNack);
    PS_PRINTF("Send Dhcp Mac Frame Succ      :    %d \r\n",g_stDhcpStatStru.ulSendDhcpPktSucc);
    PS_PRINTF("Send Dhcp Mac Frame Fail      :    %d \r\n",g_stDhcpStatStru.ulSendDhcpPktFail);

    return;
}



