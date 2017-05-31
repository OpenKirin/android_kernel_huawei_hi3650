

#ifndef __MDRV_ACORE_EFUSE_H__
#define __MDRV_ACORE_EFUSE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_efuse_common.h"

    /*************************************************
     *  �� �� ��   : mdrv_efuse_get_chipid
     *  ��������   : mdrv_efuse_get_chipid
     *  �������   : buf: data buffer
     *               len: length of the group
     *  �������   :
     *  �� �� ֵ   : OK                (0)
     *               BUF_ERROR         (-55)
     *               LEN_ERROR         (-56)
     *               READ_EFUSE_ERROR  (-57)
     *  �޸���ʷ   :
     *  ��    �� : 2013��8��12��
     *  ��    �� : l00225826
     *  �޸����� : �����ɺ���
     *************************************************/
    int mdrv_efuse_get_chipid(unsigned char* buf,int length);

    /*************************************************
     *  �� �� ��   : mdrv_efuse_get_dieid
     *  ��������   : mdrv_efuse_get_dieid
     *  �������   : buf: data buffer
     *               len: length of the buf in bytes
     *  �������   :
     *  �� �� ֵ   : OK                (0)
     *               BUF_ERROR         (-55)
     *               LEN_ERROR         (-56)
     *               READ_EFUSE_ERROR  (-57)

     *  �޸���ʷ   :
     *  ��    �� : 2013��8��12��
     *  ��    �� : l00225826
     *  �޸����� : �����ɺ���
     *************************************************/
    int mdrv_efuse_get_dieid(unsigned char* buf, int length);


#define MDRV_EFUSE_IOCTL_CMD_GET_SOCID          (0)
#define MDRV_EFUSE_IOCTL_CMD_SET_KCE            (1)
#define MDRV_EFUSE_IOCTL_CMD_GET_KCE            (2)
#define MDRV_EFUSE_IOCTL_CMD_SET_SECURESTATE    (3)
#define MDRV_EFUSE_IOCTL_CMD_GET_SECURESTATE    (4)
#define MDRV_EFUSE_IOCTL_CMD_SET_SECUREDEBUG    (5)
#define MDRV_EFUSE_IOCTL_CMD_GET_SECUREDEBUG    (6)
#define MDRV_EFUSE_IOCTL_CMD_SET_DBGEN          (7)
#define MDRV_EFUSE_IOCTL_CMD_GET_DBGEN          (8)
#define MDRV_EFUSE_IOCTL_CMD_SET_NIDEN          (9)
#define MDRV_EFUSE_IOCTL_CMD_GET_NIDEN          (10)
#define MDRV_EFUSE_IOCTL_CMD_SET_SPIDEN         (11)
#define MDRV_EFUSE_IOCTL_CMD_GET_SPIDEN         (12)
#define MDRV_EFUSE_IOCTL_CMD_SET_SPNIDEN        (13)
#define MDRV_EFUSE_IOCTL_CMD_GET_SPNIDEN        (14)
#define MDRV_EFUSE_IOCTL_CMD_SET_HIFIDBGEN      (15)
#define MDRV_EFUSE_IOCTL_CMD_GET_HIFIDBGEN      (16)
#define MDRV_EFUSE_IOCTL_CMD_SET_BBE16DBGEN     (17)
#define MDRV_EFUSE_IOCTL_CMD_GET_BBE16DBGEN     (18)
#define MDRV_EFUSE_IOCTL_CMD_SET_CSDEVICEEN     (19)
#define MDRV_EFUSE_IOCTL_CMD_GET_CSDEVICEEN     (20)
#define MDRV_EFUSE_IOCTL_CMD_SET_JTAGEN         (21)
#define MDRV_EFUSE_IOCTL_CMD_GET_JTAGEN         (22)
#define MDRV_EFUSE_IOCTL_CMD_SET_SECDBGRESET    (23)
#define MDRV_EFUSE_IOCTL_CMD_GET_SECDBGRESET    (24)
#define MDRV_EFUSE_IOCTL_CMD_SET_CSRESET        (25)
#define MDRV_EFUSE_IOCTL_CMD_GET_CSRESET        (26)
#define MDRV_EFUSE_IOCTL_CMD_SET_DFTSEL         (27)
#define MDRV_EFUSE_IOCTL_CMD_GET_DFTSEL         (28)
#define MDRV_EFUSE_IOCTL_CMD_SET_AUTHKEY        (29)
#define MDRV_EFUSE_IOCTL_CMD_GET_AUTHKEY        (30)
#define MDRV_EFUSE_IOCTL_CMD_SET_AUTHKEYRD      (31)
#define MDRV_EFUSE_IOCTL_CMD_GET_AUTHKEYRD      (32)
#define MDRV_EFUSE_IOCTL_CMD_SET_NSIVERIFY      (33)
#define MDRV_EFUSE_IOCTL_CMD_GET_NSIVERIFY      (34)


    /*************************************************
     *  �� �� ��   : mdrv_efuse_ioctl
     *  ��������   : Efuse����������д�Ͷ�ȡ
     *  �������   : cmd: MDRV_EFUSE_IOCTL_CMD_ ��صĺ꣬ÿ������ͬ����AT�����Ӧ
     *               arg: ��������Ӧ�Ĳ���
     *               buf: data buffer
     *               len: length of the group
     *  �������   : ��
     *  �� �� ֵ   : ret
     *
     *

     MDRV_EFUSE_IOCTL_CMD_GET_SOCID
        arg     NA
        buf     Buffer��ַ
        len     Buffer���ȣ���С��8
        ret     <0 -- ERROR
                0  -- OK
        desciption      ^SOCID? ��ȡоƬ��SOCID(256 bits)

     MDRV_EFUSE_IOCTL_CMD_SET_KCE
        arg     NA
        buf     Buffer��ַ
        len     Buffer���ȣ���С��4
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^KCE=<value> ���� 128bit ��KEY,����image�ļӽ���

     MDRV_EFUSE_IOCTL_CMD_GET_KCE
        arg     NA
        buf     Buffer��ַ
        len     Buffer���ȣ���С��4
        ret     <0 -- ERROR
                0  -- OK
        desciption      KCE���ɶ�ȡ���������ò���

     MDRV_EFUSE_IOCTL_CMD_SET_SECURESTATE
        arg     0  -- δ����оƬ��ȫ״̬
                1  -- ����оƬΪ��ȫ״̬
                2  -- ����оƬΪ�ǰ�ȫ״̬
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^SECURESTATE=<value> ����оƬ�İ�ȫ״̬

     MDRV_EFUSE_IOCTL_CMD_GET_SECURESTATE
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- δ����оƬ��ȫ״̬
                1  -- ����оƬΪ��ȫ״̬
                2  -- ����оƬΪ�ǰ�ȫ״̬
        desciption      ^SECURESTATE? ��ȡоƬ�İ�ȫ״̬

     MDRV_EFUSE_IOCTL_CMD_SET_SECUREDEBUG
        arg     0  -- Secure privilege debug
                1  -- ͨ�����뱣���ķ�ʽ���м�Ȩ����Ȩͨ��֮�����ʹ��debug����
                2  -- �����ź���eFuse�е���дֵȷ��
                3  -- DCU����
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^SECUREDEBUG=<value> �����ն�оƬ��DEBUG ģʽ

     MDRV_EFUSE_IOCTL_CMD_GET_SECUREDEBUG
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- Secure privilege debug
                1  -- ͨ�����뱣���ķ�ʽ���м�Ȩ����Ȩͨ��֮�����ʹ��debug����
                2  -- �����ź���eFuse�е���дֵȷ��
                3  -- DCU����
        desciption      ^SECUREDEBUG? ��ȡоƬ��DEBUG ģʽ

     MDRV_EFUSE_IOCTL_CMD_SET_DBGEN
        arg     0  -- ��
                1  -- �ر�
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^DEBUGEN=<value> �����Ƿ����ǰ�ȫ��������ʽ���Թ���(ֻ��AT^SECUREDEBUGΪ0b10ʱ��Ч)

     MDRV_EFUSE_IOCTL_CMD_GET_DBGEN
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- ��
                1  -- �ر�
        desciption      ^DEBUGEN? ��ȡ�Ƿ����ǰ�ȫ��������ʽ���Թ���(ֻ��AT^SECUREDEBUGΪ0b10ʱ��Ч)

     MDRV_EFUSE_IOCTL_CMD_SET_NIDEN
        arg     0  -- ��
                1  -- �ر�
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^NIDEN=<value> �����Ƿ����ǰ�ȫ���������ʽ���Թ���(ֻ��AT^SECUREDEBUGΪ0b10ʱ��Ч)

     MDRV_EFUSE_IOCTL_CMD_GET_NIDEN
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- ��
                1  -- �ر�
        desciption      ^NIDEN? ��ȡ�Ƿ����ǰ�ȫ���������ʽ���Թ���(ֻ��AT^SECUREDEBUGΪ0b10ʱ��Ч)

     MDRV_EFUSE_IOCTL_CMD_SET_SPIDEN
        arg     0  -- ��
                1  -- �ر�
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^SPIDEN=<value> �����Ƿ�����ȫ��������ʽ���Թ���(ֻ��AT^SECUREDEBUGΪ0b10ʱ��Ч)

     MDRV_EFUSE_IOCTL_CMD_GET_SPIDEN
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- ��
                1  -- �ر�
        desciption      ^SPIDEN? ��ȡ�Ƿ�����ȫ��������ʽ���Թ���(ֻ��AT^SECUREDEBUGΪ0b10ʱ��Ч)

     MDRV_EFUSE_IOCTL_CMD_SET_SPNIDEN
        arg     0  -- ��
                1  -- �ر�
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^SPNIDEN=<value> �����Ƿ�����ȫ���������ʽ���Թ���(ֻ��AT^SECUREDEBUGΪ0b10ʱ��Ч)

     MDRV_EFUSE_IOCTL_CMD_GET_SPNIDEN
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- ��
                1  -- �ر�
        desciption      ^SPNIDEN? ��ȡ�Ƿ�����ȫ���������ʽ���Թ���(ֻ��AT^SECUREDEBUGΪ0b10ʱ��Ч)

     MDRV_EFUSE_IOCTL_CMD_SET_HIFIDBGEN
        arg     0  -- ��
                1  -- �ر�
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^HIFIDBGEN=<value> �����Ƿ���HiFi���Թ���(ֻ��AT^SECUREDEBUGΪ0b10ʱ��Ч)

     MDRV_EFUSE_IOCTL_CMD_GET_HIFIDBGEN
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- ��
                1  -- �ر�
        desciption      ^HIFIDBGEN? ��ȡ�Ƿ���HiFi���Թ���(ֻ��AT^SECUREDEBUGΪ0b10ʱ��Ч)

     MDRV_EFUSE_IOCTL_CMD_SET_BBE16DBGEN
        arg     0  -- ��
                1  -- �ر�
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^BBE16DBGEN=<value> �����Ƿ���BBE16���Թ���(ֻ��AT^SECUREDEBUGΪ0b10ʱ��Ч)

     MDRV_EFUSE_IOCTL_CMD_GET_BBE16DBGEN
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- ��
                1  -- �ر�
        desciption      ^BBE16DBGEN? ��ȡ�Ƿ���BBE16���Թ���(ֻ��AT^SECUREDEBUGΪ0b10ʱ��Ч)

     MDRV_EFUSE_IOCTL_CMD_SET_CSDEVICEEN
        arg     0  -- ��
                1  -- �ر�
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^CSDEVICEEN=<value> �����Ƿ���Coresight���Թ���(ֻ��AT^SECUREDEBUGΪ0b10ʱ��Ч)

     MDRV_EFUSE_IOCTL_CMD_GET_CSDEVICEEN
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- ��
                1  -- �ر�
        desciption      ^CSDEVICEEN? ��ȡ�Ƿ���Coresight���Թ���(ֻ��AT^SECUREDEBUGΪ0b10ʱ��Ч)

     MDRV_EFUSE_IOCTL_CMD_SET_JTAGEN
        arg     0  -- ��
                1  -- �ر�
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^JTAGEN=<value> �����Ƿ���JTAG���Թ���

     MDRV_EFUSE_IOCTL_CMD_GET_JTAGEN
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- ��
                1  -- �ر�
        desciption      ^JTAGEN? ��ȡ�Ƿ���JTAG���Թ���

     MDRV_EFUSE_IOCTL_CMD_SET_SECDBGRESET
        arg     0  -- Ĭ�ϲ���λ
                1  -- ��λ
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^SECDBGRESET=<value> �����Ƿ��ڽ��а�ȫ�������ʱ����ʱ��λSEC Engine

     MDRV_EFUSE_IOCTL_CMD_GET_SECDBGRESET
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- Ĭ�ϲ���λ
                1  -- ��λ
        desciption      ^SECDBGRESET? ��ȡ�Ƿ��ڽ��а�ȫ�������ʱ����ʱ��λSEC Engine

     MDRV_EFUSE_IOCTL_CMD_SET_CSRESET
        arg     0  -- Ĭ�ϲ���λ
                1  -- ��λ
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^CSRESET=<value> �����Ƿ�����Coresight����ʱ����ʱ��λSEC Engine

     MDRV_EFUSE_IOCTL_CMD_GET_CSRESET
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- Ĭ�ϲ���λ
                1  -- ��λ"
        desciption      ^CSRESET? ��ȡ�Ƿ�����Coresight����ʱ����ʱ��λSEC Engine

     MDRV_EFUSE_IOCTL_CMD_SET_DFTSEL
        arg     0  -- ��״̬
                1  -- �ر�״̬
                2/3 -- ���ùر�״̬
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^DFTSEL=<value> ����DFTSCAN �ĵȼ�

     MDRV_EFUSE_IOCTL_CMD_GET_DFTSEL
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- ��״̬
                1  -- �ر�״̬
                2/3 -- ���ùر�״̬
        desciption      ^DFTSEL? ��ȡDFTSCAN �ĵȼ�

     MDRV_EFUSE_IOCTL_CMD_SET_AUTHKEY
        arg     NA
        buf     Buffer��ַ
        len     Buffer���ȣ���С��2
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^AUTHKEY=<value> ���� 64 bits �� DFT �������Ȩ����֤����

     MDRV_EFUSE_IOCTL_CMD_GET_AUTHKEY
        arg     NA
        buf     Buffer��ַ
        len     Buffer���ȣ���С��2
        ret     <0 -- ERROR
                0  -- OK
        desciption      ^AUTHKEY? ��ȡоƬ64 bits �� DFT �������Ȩ����֤����

     MDRV_EFUSE_IOCTL_CMD_SET_AUTHKEYRD
        arg     0  -- ����ɶ�
                1  -- ������ɶ�
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^AUTHKEYRD=<value> ����AUTHKEY �Ƿ�ɶ�

     MDRV_EFUSE_IOCTL_CMD_GET_AUTHKEYRD
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- ����ɶ�
                1  -- ������ɶ�
        desciption      ^AUTHKEYRD? ��ȡAUTHKEY �Ƿ�ɶ�

     MDRV_EFUSE_IOCTL_CMD_SET_NSIVERIFY
        arg     0  -- �ر�У��
                1  -- ��У��
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^NSIVERIFY=<value> �����Ƿ����ǰ�ȫ��Ʒ����������У��

     MDRV_EFUSE_IOCTL_CMD_GET_NSIVERIFY
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- �ر�У��
                1  -- ��У��
        desciption      ^NSIVERIFY? ��ȡ�Ƿ����ǰ�ȫ��Ʒ����������У��

     *  �޸���ʷ   :
     *  ��    �� : 2015��11��28��
     *  ��    �� : z00227143
     *  �޸����� : �����ɺ���
     *************************************************/
    int mdrv_efuse_ioctl(int cmd, int arg, unsigned char* buf, int len);


#ifdef __cplusplus
}
#endif
#endif

