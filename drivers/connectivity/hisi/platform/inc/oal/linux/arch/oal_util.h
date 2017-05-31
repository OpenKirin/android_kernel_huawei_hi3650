/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : oal_util.h
  �� �� ��   : ����
  ��    ��   : c59720
  ��������   : 2012��9��25��
  ����޸�   :
  ��������   : oal_util_linux.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��25��
    ��    ��   : c59720
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OAL_LINUX_UTIL_H__
#define __OAL_LINUX_UTIL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
/*lint -e322*/
#include <linux/compiler.h>
#include <linux/kernel.h>
#include <linux/kallsyms.h>
#include <asm/string.h>
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#include <asm/system.h>
#endif
#include <linux/thread_info.h>
#include <asm/byteorder.h>
#include <linux/byteorder/generic.h>
#include <linux/bitops.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <asm/delay.h>
#include <asm/memory.h>

#include <linux/kobject.h>      /* hi1102-cb add sys for 51/02 */
#include <linux/device.h>
#include <linux/sysfs.h>
#include <linux/etherdevice.h>  /* hi1102-cb for random mac address */
/*lint +e322*/

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* 32�ֽ����С��ת�� */
#define OAL_SWAP_BYTEORDER_32(_val)        \
        ((((_val) & 0x000000FF) << 24) +     \
        (((_val) & 0x0000FF00) << 8) +       \
        (((_val) & 0x00FF0000) >> 8) +       \
        (((_val) & 0xFF000000) >> 24))

#define OAL_CONST                                   const

/* ��ȡCORE ID */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#define OAL_GET_CORE_ID()    (0)
#else                                   /* ��offload�ܹ� */
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
#define OAL_GET_CORE_ID()    smp_processor_id()
#else
#define OAL_GET_CORE_ID()    (0)        /* ��Ҫ��E5ƽ̨ʹ�� */
#endif
#endif

typedef oal_uint    oal_bitops;

typedef struct file              oal_file_stru;
#define OAL_FILE_FAIL            OAL_PTR_NULL

#define OAL_LIKELY(_expr)       likely(_expr)
#define OAL_UNLIKELY(_expr)     unlikely(_expr)
#define OAL_FUNC_NAME           __func__
#define OAL_RET_ADDR            __builtin_return_address(0)

/* �������ַ�������ָ����ʽ�ϳ�һ���ַ��� */
#define OAL_SPRINTF             snprintf

/* �ڴ������ */
#define OAL_RMB()               rmb()

/* �ڴ�д���� */
#define OAL_WMB()               wmb()

/* �ڴ����� */
#define OAL_MB()                mb()

#define OAL_OFFSET_OF          offsetof

#define __OAL_DECLARE_PACKED    __attribute__((__packed__))

#ifndef HISI_LOG_TAG
#define HISI_LOG_TAG
#endif
#define OAL_IO_PRINT(fmt, arg...)    \
    do {                            \
            printk(KERN_DEBUG HISI_LOG_TAG ""fmt, ##arg);\
    } while(0)

#define OAL_BUG_ON(_con)        BUG_ON(_con)

#define OAL_WARN_ON(condition)  WARN_ON(condition)

#define OAL_VSPRINTF            vsnprintf

/* E5ƽ̨�������ã�ע�⣬host��ƽ̨��ͬ��MEM_BASE_ADDR��Ҫ�޸� */
#if(_PRE_TARGET_PRODUCT_TYPE_E5 == _PRE_CONFIG_TARGET_PRODUCT)
extern oal_uint32 gul_dscr_fstvirt_addr;
extern oal_uint32 gul_dscr_fstphy_addr;

#ifdef _PRE_E5_750_PLATFORM
#define  OAL_PLAT_MEM_BASE_ADDR  0x40000000
#else
#define  OAL_PLAT_MEM_BASE_ADDR  0xA0000000
#endif
#define OAL_DSCR_VIRT_TO_PHY(_virt_addr)    (((oal_uint)(_virt_addr) - (gul_dscr_fstvirt_addr)) + (gul_dscr_fstphy_addr) - OAL_PLAT_MEM_BASE_ADDR)
#define OAL_DSCR_PHY_TO_VIRT(_phy_addr)     (((oal_uint)(_phy_addr) + OAL_PLAT_MEM_BASE_ADDR) - (gul_dscr_fstphy_addr) + (gul_dscr_fstvirt_addr))
#else

#define  OAL_PLAT_MEM_BASE_ADDR  0x80000000

#define OAL_DSCR_VIRT_TO_PHY(_virt_addr)    (virt_to_phys(_virt_addr) - OAL_PLAT_MEM_BASE_ADDR)
#define OAL_DSCR_PHY_TO_VIRT(_phy_addr)     phys_to_virt((_phy_addr) + OAL_PLAT_MEM_BASE_ADDR)
#endif

/* �����ַ�������ַ֮���ת��,��Ϊnetbuf�� */
#define OAL_VIRT_TO_PHY_ADDR(_virt_addr)            (virt_to_phys(_virt_addr) - OAL_PLAT_MEM_BASE_ADDR)
#define OAL_PHY_TO_VIRT_ADDR(_phy_addr)             phys_to_virt((_phy_addr) + OAL_PLAT_MEM_BASE_ADDR)

#define OAL_CFG_FILE_PATH       ("/tmp/1151_cfg.ini")

typedef ssize_t     oal_ssize_t;    /* hi1102-cb for sys interface  51/02 */
typedef size_t      oal_size_t;
typedef struct device_attribute     oal_device_attribute_stru;
typedef struct device               oal_device_stru;
#define OAL_DEVICE_ATTR             DEVICE_ATTR
#define OAL_S_IRUGO                 S_IRUGO
#define OAL_S_IWGRP                 S_IWGRP
#define OAL_S_IWUSR                 S_IWUSR
typedef struct kobject              oal_kobject;

//#define oal_kobject_create_and_add  kobject_create_and_add
//#define oal_sysfs_create_file       sysfs_create_file

#define OAL_STRLEN                                  strlen
#define OAL_MEMCMP                                  memcmp
#define OAL_STRSTR                                  strstr
#define OAL_STRCMP                                  strcmp
#define OAL_STRNCMP                                 strncmp


/* #define oal_random_ether_addr(addr) random_ether_addr(addr) */

/* hi1102-cb for sys interface  51/02 */

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

/* #define random_ether_addr(addr) eth_random_addr(addr) */
/* static inline void eth_random_addr(u8 *addr) */
static OAL_INLINE void oal_random_ether_addr(oal_uint8 *addr)
{
   random_ether_addr(addr);
}

/*****************************************************************************
 �� �� ��  : oal_bit_atomic_test_and_set
 ��������  : ԭ�ӵĶ�ĳ��λ������1�����������ظ�λ�õľ�ֵ��
 �������  : nr: ��Ҫ���õ�λ
             p_addr��Ҫ��λ�ı�����ַ
 �������  :
 �� �� ֵ  : ����ԭ��bitλ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��11��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bitops  oal_bit_atomic_test_and_set(oal_bitops nr, OAL_VOLATILE oal_bitops *p_addr)
{
    return test_and_set_bit(nr, p_addr);
}

/*****************************************************************************
 �� �� ��  : oal_bit_atomic_clear
 ��������  : ��װ��������ϵͳƽ̨�¶�ĳ��λ����ԭ����0������
 �������  : nr: ��Ҫ�����λ
             p_addr��Ҫ����ı�����ַ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��11��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_bit_atomic_clear(oal_bitops nr, OAL_VOLATILE oal_bitops *p_addr)
{
    clear_bit(nr, p_addr);
}

/*****************************************************************************
 �� �� ��  : oal_byteorder_host_to_net_uint16
 ��������  : ��16λ�����ֽ���ת��Ϊ�����ֽ���
 �������  : us_byte: ��Ҫ�ֽ���ת���ı���
 �������  : ��
 �� �� ֵ  : ת���õı���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE __attribute_const__ oal_uint16  oal_byteorder_host_to_net_uint16(oal_uint16 us_byte)
{
    return htons(us_byte);
}

/*****************************************************************************
 �� �� ��  : oal_byteorder_host_to_net_uint16
 ��������  : ��16λ�����ֽ���ת��Ϊ�����ֽ���
 �������  : us_byte: ��Ҫ�ֽ���ת���ı���
 �������  : ��
 �� �� ֵ  : ת���õı���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE __attribute_const__ oal_uint16  oal_byteorder_net_to_host_uint16(oal_uint16 us_byte)
{
    return ntohs(us_byte);
}

/*****************************************************************************
 �� �� ��  : oal_byteorder_host_to_net_uint16
 ��������  : ��32λ�����ֽ���ת��Ϊ�����ֽ���
 �������  : us_byte: ��Ҫ�ֽ���ת���ı���
 �������  : ��
 �� �� ֵ  : ת���õı���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE __attribute_const__ oal_uint32  oal_byteorder_host_to_net_uint32(oal_uint32 ul_byte)
{
    return htonl(ul_byte);
}

/*****************************************************************************
 �� �� ��  : oal_byteorder_host_to_net_uint16
 ��������  : ��32λ�����ֽ���ת��Ϊ�����ֽ���
 �������  : us_byte: ��Ҫ�ֽ���ת���ı���
 �������  : ��
 �� �� ֵ  : ת���õı���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE __attribute_const__ oal_uint32  oal_byteorder_net_to_host_uint32(oal_uint32 ul_byte)
{
    return ntohl(ul_byte);
}

/*****************************************************************************
 �� �� ��  : oal_file_open_rw
 ��������  : ���ļ�����ʽrw��û���򴴽�
 �������  : pc_path: �ļ�·��
 �������  : ��
 �� �� ֵ  : �ļ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_file_stru* oal_file_open_rw(const oal_int8 *pc_path)
{
    oal_file_stru *file;

    file = filp_open(pc_path, (O_CREAT | O_RDWR), 0);
    if (IS_ERR(file))
    {
        return OAL_PTR_NULL;
    }

    return file;
}

/*****************************************************************************
 �� �� ��  : oal_file_open_append
 ��������  : ���ļ�,��ʽappend��û���򴴽�
 �������  : pc_path: �ļ�·��
 �������  : ��
 �� �� ֵ  : �ļ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_file_stru* oal_file_open_append(const oal_int8 *pc_path)
{
    oal_file_stru* file;

    file = filp_open(pc_path, (O_CREAT | O_APPEND), 0);
    if (IS_ERR(file))
    {
        return OAL_PTR_NULL;
    }

    return file;
}

/*****************************************************************************
 �� �� ��  : oal_file_open_rw
 ��������  : ���ļ�����ʽֻ��
 �������  : pc_path: �ļ�·��
 �������  : ��
 �� �� ֵ  : �ļ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_file_stru* oal_file_open_readonly(const oal_int8 *pc_path)
{
    oal_file_stru* file;

    file = filp_open(pc_path, (O_RDONLY), 0);
    if (IS_ERR(file))
    {
        return OAL_PTR_NULL;
    }

    return file;
}

/*****************************************************************************
 �� �� ��  : oal_file_write
 ��������  : д�ļ�
 �������  : file: �ļ����
           : pc_string: �������ݵ�ַ
           : ul_length: �������ݳ���
 �������  : ��
 �� �� ֵ  : �ļ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_file_stru* oal_file_write(oal_file_stru *file, oal_int8 *pc_string, oal_uint32 ul_length)
{
    oal_int i_ret;

    i_ret = file->f_op->write(file, pc_string, ul_length, &file->f_pos);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oal_file_close
 ��������  : �ر��ļ�
 �������  : pc_path: �ļ�·��
 �������  : ��
 �� �� ֵ  : �ļ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32 oal_file_close(oal_file_stru *file)
{
    int ret = -1;
    ret = filp_close(file, 0);
    if (0 == ret)
    {
        return OAL_SUCC;
    }
    else
    {
        return OAL_ERR_CODE_CLOSE_FILE_FAIL;
    }
}

/*****************************************************************************
 �� �� ��  : oal_file_read
 ��������  : �ں˶��ļ�����ͷ��ʼ��
 �������  : file:ָ��Ҫ��ȡ���ļ���ָ��
             puc_buf:���ļ��������ݺ��ŵ�buf
             ul_count:ָ��Ҫ��ȡ�ĳ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��10��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_file_read(oal_file_stru *file,
		                                         oal_int8 *pc_buf,
		                                         oal_uint32 ul_count)
{
    return kernel_read(file, 0, pc_buf, ul_count);
}

/*****************************************************************************
 �� �� ��  : oal_file_size
 ��������  : ��ȡ�ļ���С
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��11��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_file_size(oal_uint32   *pul_file_size)
{
    oal_file_stru     *p_file;

    p_file = oal_file_open_readonly(OAL_CFG_FILE_PATH);
    if (OAL_PTR_NULL == p_file)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pul_file_size = ((p_file->f_path).dentry)->d_inode->i_size;

    oal_file_close(p_file);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oal_atoi
 ��������  : �ַ�������ת��������
 �������  : c_string: �ַ�����ַ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��11��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_atoi(const oal_int8 *c_string)
{
    oal_int32 l_ret = 0;
    oal_int32 flag = 0;

    for ( ; ; c_string++)
    {
        switch (*c_string)
        {
            case '0'...'9':
                l_ret = 10 * l_ret + (*c_string - '0');

                break;
            case '-':
                flag=1;
                break;

            case ' ':
                continue;

            default:

                return ((0 == flag) ? l_ret:(-l_ret));;
        }
    }
}

/*****************************************************************************
 �� �� ��  : oal_itoa
 ��������  : ����ת�ַ���
 �������  : oal_int32 l_val
             oal_int8 *c_string
             oal_uint8 uc_strlen
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��28��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_itoa(oal_int32 l_val, oal_int8 *c_string, oal_uint8 uc_strlen)
{
    snprintf(c_string, uc_strlen, "%d", l_val);
}

/*****************************************************************************
 �� �� ��  : oal_strtok
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int8 *oal_strtok(oal_int8 *pc_token, OAL_CONST oal_int8 *pc_delemit, oal_int8 **ppc_context)
{
    oal_int8 *pc_str;
    OAL_CONST oal_int8 *pc_ctrl = pc_delemit;

    oal_uint8 uc_map[32];
    oal_int32 l_count;

    static oal_int8 *pc_nextoken;

    /* Clear control map */
    for (l_count = 0; l_count < 32; l_count++)
    {
        uc_map[l_count] = 0;
    }

    /* Set bits in delimiter table */
    do
    {
        uc_map[*pc_ctrl >> 3] |= (1 << (*pc_ctrl & 7));
    } while (*pc_ctrl++);

    /* Initialize str. If string is NULL, set str to the saved
    * pointer (i.e., continue breaking tokens out of the string
    * from the last strtok call) */
    if (pc_token)
    {
        pc_str = pc_token;
    }
    else
    {
        pc_str = pc_nextoken;
    }

    /* Find beginning of token (skip over leading delimiters). Note that
    * there is no token iff this loop sets str to point to the terminal
    * null (*str == '\0') */
    while ( (uc_map[*pc_str >> 3] & (1 << (*pc_str & 7))) && *pc_str )
    {
        pc_str++;
    }

    pc_token = pc_str;

    /* Find the end of the token. If it is not the end of the string,
    * put a null there. */
    for ( ; *pc_str ; pc_str++ )
    {
        if ( uc_map[*pc_str >> 3] & (1 << (*pc_str & 7)) )
        {
            *pc_str++ = '\0';
            break;
        }
    }

    /* Update nextoken (or the corresponding field in the per-thread data
    * structure */
    pc_nextoken = pc_str;

    /* Determine if a token has been found. */
    if ( pc_token == pc_str )
    {
        return NULL;
    }
    else
    {
        return pc_token;
    }
}

/* Works only for digits and letters, but small and fast */
#define TOLOWER(x) ((x) | 0x20)

#define isdigit(c)	('0' <= (c) && (c) <= '9')

#define isxdigit(c)	(('0' <= (c) && (c) <= '9') \
                 || ('a' <= (c) && (c) <= 'f') \
                 || ('A' <= (c) && (c) <= 'F'))

#define OAL_ROUND_UP        round_up
#define OAL_ROUND_DOWN      round_down

OAL_STATIC OAL_INLINE unsigned int simple_guess_base(const char *cp)
{
    if (cp[0] == '0') {
        if (TOLOWER(cp[1]) == 'x' && isxdigit(cp[2]))
            return 16;
        else
            return 8;
    } else {
        return 10;
    }
}

OAL_STATIC OAL_INLINE unsigned long long oal_simple_strtoull(const oal_int8 *cp, oal_int8 **endp, unsigned int base)
{
    unsigned long long result = 0;

    if (!base)
        base = simple_guess_base(cp);

    if (base == 16 && cp[0] == '0' && TOLOWER(cp[1]) == 'x')
        cp += 2;

    while (isxdigit(*cp)) {
        unsigned int value;

        value = isdigit(*cp) ? *cp - '0' : TOLOWER(*cp) - 'a' + 10;
        if (value >= base)
            break;
        result = result * base + value;
        cp++;
    }
    if (endp)
        *endp = (oal_int8 *)cp;

    return result;
}

/*****************************************************************************
 �� �� ��  : oal_strtol
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��3��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int  oal_strtol(OAL_CONST oal_int8 *pc_nptr, oal_int8 **ppc_endptr, oal_int32 l_base)
{
    /* �����ո� */
    while (' ' == (*pc_nptr))
    {
        pc_nptr++;
    }

    if (*pc_nptr == '-')
        return -oal_simple_strtoull(pc_nptr + 1, ppc_endptr, l_base);

    return oal_simple_strtoull(pc_nptr, ppc_endptr, l_base);
}

/*****************************************************************************
 �� �� ��  : oal_udelay
 ��������  : ΢�뼶�ӳٺ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��8��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_udelay(oal_uint u_loops)
{
    udelay(u_loops);
}

/*****************************************************************************
 �� �� ��  : oal_mdelay
 ��������  : ���뼶�ӳٺ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��6��
    ��    ��   : daihu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_mdelay(oal_uint u_loops)
{
    mdelay(u_loops);
}

/*****************************************************************************
 �� �� ��  : oal_kallsyms_lookup_name
 ��������  : ����ȫ�ֱ������ֲ���ȫ�ֱ�����ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����0������δ�ҵ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��26��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_kallsyms_lookup_name(OAL_CONST oal_uint8 *uc_var_name)
{
    return kallsyms_lookup_name(uc_var_name);
}


/*****************************************************************************
 �� �� ��  : oal_dump_stack
 ��������  : ��ӡ��������ջ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��3��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_dump_stack(oal_void)
{
#if(_PRE_CONFIG_TARGET_PRODUCT != _PRE_TARGET_PRODUCT_TYPE_WS835DMB)
    //835��Ʒ����dump_stack�ᴥ��ϵͳ����
    dump_stack();
#endif
}

/*****************************************************************************
 �� �� ��  : oal_msleep
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_msleep(oal_uint32 ul_usecs)
{
    msleep(ul_usecs);
}

/*****************************************************************************
 �� �� ��  : oal_strncpy
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��30��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int8 *oal_strncpy(oal_int8 *pc_dest, OAL_CONST oal_int8 *pc_src, oal_uint32 ul_len)
{
    return strncpy((oal_int8 *)pc_dest, pc_src, ul_len);
}

/*****************************************************************************
 �� �� ��  : oal_print_hex_dump
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   :
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_print_hex_dump(oal_uint8*addr, oal_int32 len, oal_int32 groupsize,oal_int8* pre_str)
{
#ifdef CONFIG_PRINTK
    OAL_REFERENCE(groupsize);
    printk(KERN_DEBUG"buf %p,len:%d\n",
           addr,
           len);
    print_hex_dump(KERN_DEBUG, pre_str, DUMP_PREFIX_ADDRESS, 16, 1,
		       addr, len, true);
    printk(KERN_DEBUG"\n");
#endif
}
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_util.h */
