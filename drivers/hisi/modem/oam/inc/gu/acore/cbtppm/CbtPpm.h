

/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CbtPpm.h
  �� �� ��   : ����
  ��    ��   : h59254
  ��������   : 2014��5��31��
  ����޸�   :
  ��������   : CbtPpm.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : �����ļ�
******************************************************************************/

#ifndef __CBT_PPM_H__
#define __CBT_PPM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "omnvinterface.h"
#include "mdrv.h"

#if (FEATURE_HISOCKET == FEATURE_ON)
#include "hisocket.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if (FEATURE_HISOCKET == FEATURE_ON)

#define CBTPPM_SOCK_MSG_LEN             (1000)

#define CBTPPM_SOCK_PORT_NUM            (20250)

#define CBTPPM_SOCKET_NUM_MAX           (1)

#if  (VOS_LINUX == VOS_OS_VER)
#define CBTPPM_SOCK_NULL                (-1)


#define CBTPPM_SOCKET_ERROR             (VOS_ERROR)


#define CBT_IP_NULL         0
#define CBT_Ip_sockaddr     sockaddr
#define CBT_Ip_socklen_t    int
#define CBT_Ip_fd           int
#define CBT_Ip_fd_set       hi_fd_set


#define CBT_socket(domain,type,protocol)        hi_socket(domain, type, protocol)

#define CBT_shutdown(fd,how)                    do{\
                                                    hi_shutdown((CBT_Ip_fd)fd, how);\
                                                    hi_close((CBT_Ip_fd)fd);\
                                                }while(0)
                                            
#define CBT_closesocket(s)                      CBT_shutdown(s, SHUT_RDWR)

#define CBT_bind(fd,addr,addrlen)               hi_bind((CBT_Ip_fd)fd, (struct  CBT_Ip_sockaddr *)addr, (CBT_Ip_socklen_t)addrlen)
#define CBT_accept(fd,addr,addrlenp)            hi_accept((CBT_Ip_fd)fd, (struct  CBT_Ip_sockaddr *)addr, (CBT_Ip_socklen_t *)addrlenp)
#define CBT_listen(fd,backlog)                  hi_listen((CBT_Ip_fd)fd, backlog)
#define CBT_select(nfds,rf,wf,ef,t)             hi_select(nfds, (CBT_Ip_fd_set *)rf, (CBT_Ip_fd_set *)wf, CBT_IP_NULL, t)
#define CBT_recv(fd,buf,len,flags)              hi_recv((CBT_Ip_fd)fd, (void *)buf, len, flags)
#define CBT_send(fd,msg,len,flags)              hi_send((CBT_Ip_fd)fd, (void *)msg, len, flags)
#else
#define CBTPPM_SOCK_NULL                       (0)

#define CBT_Ip_fd_set                          fd_set

#endif

#endif

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* UDI�豸��� */
enum OM_PROT_HANDLE_ENUM
{
    OM_USB_CBT_PORT_HANDLE      =   0,
    OM_PORT_HANDLE_BUTT
};

typedef VOS_UINT32  OM_PROT_HANDLE_ENUM_UINT32;

enum OM_LOGIC_CHANNEL_ENUM
{
     OM_LOGIC_CHANNEL_CBT = 0,
     OM_LOGIC_CHANNEL_BUTT
};

typedef VOS_UINT32     OM_LOGIC_CHANNEL_ENUM_UINT32;

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
/* ���ڼ�¼VCOM������Ϣ */
typedef struct
{
    VOS_UINT32                          ulVCOMSendSn;
    VOS_UINT32                          ulVCOMSendNum;
    VOS_UINT32                          ulVCOMSendLen;
    VOS_UINT32                          ulVCOMSendErrNum;
    VOS_UINT32                          ulVCOMSendErrLen;

    VOS_UINT32                          ulVCOMRcvSn;
    VOS_UINT32                          ulVCOMRcvNum;
    VOS_UINT32                          ulVCOMRcvLen;
    VOS_UINT32                          ulVCOMRcvErrNum;
    VOS_UINT32                          ulVCOMRcvErrLen;
}CBT_ACPU_VCOM_DEBUG_INFO;

#if (FEATURE_HISOCKET == FEATURE_ON)

#if (VOS_LINUX == VOS_OS_VER)

typedef int    CBTPPM_SOCKET;

#else

typedef unsigned int     CBTPPM_SOCKET;

#endif

typedef struct
{
    CBTPPM_SOCKET                       socket;
    CBTPPM_SOCKET                       listener;
    VOS_SEM                             SmClose;
    VOS_CHAR                            aucBuf[CBTPPM_SOCK_MSG_LEN];
}CBTPPM_SOCKET_CTRL_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulListernNum1;
    VOS_UINT32                          ulListernNum2;
    VOS_UINT32                          ulRcvData;
    VOS_UINT32                          ulFailToProcess;
    VOS_UINT32                          ulSndData;
    VOS_UINT32                          ulFailToSend;
}CBTPPM_SOCKET_DEBUG_INFO_STRU;

#endif

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_UINT32 CBTPPM_OamCbtPortDataSnd(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen);

VOS_UINT32 CBTPPM_OamUsbCbtSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen);

VOS_VOID   CBTPPM_OamUsbCbtPortClose(VOS_VOID);

VOS_VOID   CBTPPM_OamUsbCbtPortOpen(VOS_VOID);

VOS_INT32  CBTPPM_OamUsbCbtReadDataCB(VOS_VOID);

VOS_VOID   CBTPPM_OamUsbCbtWriteDataCB(VOS_UINT8* pucVirData, VOS_UINT8* pucPhyData, VOS_INT lLen);

VOS_VOID   CBTPPM_OamUsbCbtStatusCB(ACM_EVT_E enPortState);

VOS_VOID   CBTPPM_OamCbtPortDataInit(OM_PROT_HANDLE_ENUM_UINT32          enHandle,
                                                 VOS_VOID                            *pReadCB,
                                                 VOS_VOID                            *pWriteCB,
                                                 VOS_VOID                            *pStateCB);

VOS_UINT32 CBTPPM_OamUsbCbtPortInit(VOS_VOID);

VOS_INT    CBTPPM_OamVComCbtReadData(VOS_UINT8 ucDevIndex, VOS_UINT8 *pData, VOS_UINT32 ullength);

VOS_UINT32 CBTPPM_OamVComCbtSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen);

VOS_VOID   CBTPPM_OamVComCbtPortInit(VOS_VOID);

VOS_VOID   CBTPPM_OamCbtPortInit(VOS_VOID);

VOS_UINT32 PPM_DisconnectGUPort(OM_LOGIC_CHANNEL_ENUM_UINT32 enChannel);

VOS_UINT32 CBTPPM_SocketTaskInit(VOS_VOID);

VOS_VOID CBTPPM_SocketPortInit(VOS_VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of cpm.h */
