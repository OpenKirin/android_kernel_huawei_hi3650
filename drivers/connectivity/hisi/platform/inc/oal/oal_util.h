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

#ifndef __OAL_UTIL_H__
#define __OAL_UTIL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_types.h"
#include "oal_mm.h"
#include "arch/oal_util.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define OAL_VA_START            va_start
#define OAL_VA_END              va_end

#define OAL_VA_LIST             va_list

/* ƴ��Ϊ16 bit���� 32bit */
#define OAL_MAKE_WORD16(lsb, msb) ((((oal_uint16)(msb) << 8) & 0xFF00) | (lsb))
#define OAL_MAKE_WORD32(lsw, msw) ((((oal_uint32)(msw) << 16) & 0xFFFF0000) | (lsw))


/* ����Ϊ�ֽڶ��������ĳ��� */
#define OAL_ROUNDUP(_old_len, _align)  ((((_old_len) + ((_align) - 1)) / (_align)) * (_align))

/* increment with wrap-around */
#define OAL_INCR(_l, _sz)   (_l)++; (_l) &= ((_sz) - 1)
#define OAL_DECR(_l, _sz)   (_l)--; (_l) &= ((_sz) - 1)

/* ��ȡ��С */
#define OAL_SIZEOF                                  sizeof

/* ��ȡ�����С */
#define OAL_ARRAY_SIZE(_ast_array)                  (sizeof(_ast_array) / sizeof((_ast_array)[0]))

/* ���ֽڶ��� */
#define OAL_GET_4BYTE_ALIGN_VALUE(_ul_size)         (((_ul_size) + 0x03) & (~0x03))

/* ��ȡ��ǰ�߳���Ϣ */
#define OAL_CURRENT_TASK     (current_thread_info()->task)

#define OAL_SWAP_BYTEORDER_16(_val) ((((_val) & 0x00FF) << 8) + (((_val) & 0xFF00) >> 8))

#if (_PRE_BIG_CPU_ENDIAN == _PRE_CPU_ENDIAN)          /* BIG_ENDIAN */
#define OAL_BYTEORDER_TO_LE32(_val)        OAL_SWAP_BYTEORDER_32(_val)
#define OAL_BYTEORDER_TO_LE16(_val)        OAL_SWAP_BYTEORDER_16(_val)
#define OAL_MASK_INVERSE(_len, _offset)    ((oal_uint32)(OAL_SWAP_BYTEORDER_32(~(((1 << (_len)) - 1) << (_offset)))))
#define OAL_MASK(_len, _offset)            ((oal_uint32)(OAL_SWAP_BYTEORDER_32(((1 << (_len)) - 1) << (_offset))))
#define OAL_NTOH_16(_val)                  (_val)
#define OAL_NTOH_32(_val)                  (_val)
#define OAL_HTON_16(_val)                  (_val)
#define OAL_HTON_32(_val)                  (_val)

#elif (_PRE_LITTLE_CPU_ENDIAN == _PRE_CPU_ENDIAN)     /* LITTLE_ENDIAN */
#define OAL_BYTEORDER_TO_LE32(_val)        (_val)
#define OAL_BYTEORDER_TO_LE16(_val)        (_val)
#define OAL_MASK_INVERSE(_len, _offset)    ((oal_uint32)(~(((1UL << (_len)) - 1) << (_offset))))
#define OAL_MASK(_len, _offset)            ((oal_uint32)(((1UL << (_len)) - 1) << (_offset)))
#define OAL_NTOH_16(_val)                  OAL_SWAP_BYTEORDER_16(_val)
#define OAL_NTOH_32(_val)                  OAL_SWAP_BYTEORDER_32(_val)
#define OAL_HTON_16(_val)                  OAL_SWAP_BYTEORDER_16(_val)
#define OAL_HTON_32(_val)                  OAL_SWAP_BYTEORDER_32(_val)

#endif



#ifndef atomic_inc_return
#define oal_atomic_inc_return(a)    (0)
#else
#define oal_atomic_inc_return   atomic_inc_return
#endif

#if 0  /* �಻�� */
#ifndef current
#define current (0)
#endif
#endif

/* �ȽϺ� */
#define OAL_MIN(_A, _B) (((_A) < (_B))? (_A) : (_B))

/* �ȽϺ� */
#define OAL_MAX(_A, _B) (((_A) > (_B))? (_A) : (_B))

#define OAL_SUB(_A, _B) (((_A) > (_B))? ((_A) - (_B)) : (0))

#define OAL_ABSOLUTE_SUB(_A, _B) (((_A) > (_B))? ((_A) - (_B)) : ((_B) - (_A)))

/* ��ĳ���豸��ȡĳ���Ĵ�����ַ��32-bit�Ĵ�����ֵ��*/
#define OAL_REG_READ32(_addr)    \
        *((OAL_VOLATILE oal_uint32 *)(_addr))

#define OAL_REG_READ16(_addr)    \
    *((OAL_VOLATILE oal_uint16 *)(_addr))

/* ��ĳ���豸ĳ��32-bit�Ĵ�����ַд��ĳ��ֵ */
#define OAL_REG_WRITE32(_addr, _val)    \
    (*((OAL_VOLATILE oal_uint32 *)(_addr)) = (_val))
#define OAL_REG_WRITE16(_addr, _val)    \
    (*((OAL_VOLATILE oal_uint16 *)(_addr)) = (_val))

/* Is val aligned to "align" ("align" must be power of 2) */
#ifndef IS_ALIGNED
#define OAL_IS_ALIGNED(val, align)		\
	(((oal_uint32)(val) & ((align) - 1)) == 0)
#else
#define OAL_IS_ALIGNED  IS_ALIGNED
#endif


/* Bit Values */
#define BIT31                   ((oal_uint32)(1UL << 31))
#define BIT30                   ((oal_uint32)(1 << 30))
#define BIT29                   ((oal_uint32)(1 << 29))
#define BIT28                   ((oal_uint32)(1 << 28))
#define BIT27                   ((oal_uint32)(1 << 27))
#define BIT26                   ((oal_uint32)(1 << 26))
#define BIT25                   ((oal_uint32)(1 << 25))
#define BIT24                   ((oal_uint32)(1 << 24))
#define BIT23                   ((oal_uint32)(1 << 23))
#define BIT22                   ((oal_uint32)(1 << 22))
#define BIT21                   ((oal_uint32)(1 << 21))
#define BIT20                   ((oal_uint32)(1 << 20))
#define BIT19                   ((oal_uint32)(1 << 19))
#define BIT18                   ((oal_uint32)(1 << 18))
#define BIT17                   ((oal_uint32)(1 << 17))
#define BIT16                   ((oal_uint32)(1 << 16))
#define BIT15                   ((oal_uint32)(1 << 15))
#define BIT14                   ((oal_uint32)(1 << 14))
#define BIT13                   ((oal_uint32)(1 << 13))
#define BIT12                   ((oal_uint32)(1 << 12))
#define BIT11                   ((oal_uint32)(1 << 11))
#define BIT10                   ((oal_uint32)(1 << 10))
#define BIT9                    ((oal_uint32)(1 << 9))
#define BIT8                    ((oal_uint32)(1 << 8))
#define BIT7                    ((oal_uint32)(1 << 7))
#define BIT6                    ((oal_uint32)(1 << 6))
#define BIT5                    ((oal_uint32)(1 << 5))
#define BIT4                    ((oal_uint32)(1 << 4))
#define BIT3                    ((oal_uint32)(1 << 3))
#define BIT2                    ((oal_uint32)(1 << 2))
#define BIT1                    ((oal_uint32)(1 << 1))
#define BIT0                    ((oal_uint32)(1 << 0))
#define ALL                     0xFFFF

#define BIT(nr)                 (1UL << (nr))

#define OAL_BITS_PER_BYTE       8   /* һ���ֽ��а�����bit��Ŀ */


/* λ���� */
#define OAL_WRITE_BITS(_data, _val, _bits, _pos)    do{\
        (_data) &= ~((((oal_uint32)1 << (_bits)) - 1) << (_pos));\
        (_data) |= (((_val) & (((oal_uint32)1 << (_bits)) - 1)) << (_pos));\
    }while(0)

#define OAL_GET_BITS(_data, _bits, _pos)      (((_data) >> (_pos)) & (((oal_uint32)1 << (_bits)) - 1))


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
#ifdef _PRE_CONFIG_HISI_PANIC_DUMP_SUPPORT
typedef  struct _hwifi_panic_log_   hwifi_panic_log;
typedef oal_int32 (* hwifi_panic_log_cb)(oal_void* data,oal_uint8*pst_buf,oal_int32 buf_len);
struct _hwifi_panic_log_
{
    struct list_head list;
    /*the log module name*/
    char* name;
    hwifi_panic_log_cb    cb;
    oal_void* data;
};
#define DECLARE_WIFI_PANIC_STRU(module_name,func) \
        hwifi_panic_log module_name = \
        {\
            .name = #module_name,\
            .cb = (hwifi_panic_log_cb)func,\
        }
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
#ifdef _PRE_CONFIG_HISI_PANIC_DUMP_SUPPORT
/*****************************************************************************
 �� �� ��  : hwifi_panic_log_register
 ��������  : Kernl Panic �Ļص�����ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��16��
    ��    ��   : z00262551
    �޸�����   : �����ɺ���

*****************************************************************************/
extern oal_void hwifi_panic_log_register(hwifi_panic_log* log, void* data);
extern oal_void hwifi_panic_log_dump(char* print_level);
#else
OAL_STATIC OAL_INLINE oal_void hwifi_panic_log_dump(char* print_level)
{
}
#endif

/*****************************************************************************
 �� �� ��  : oal_strtohex
 ��������  : ��һ���ַ�ת����16������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_strtohex(const oal_int8 *c_string)
{
    oal_uint8 uc_ret = 0;

    if (*c_string >= '0' && *c_string <= '9')
    {
        uc_ret = (oal_uint8)(*c_string - '0');
    }
    else if (*c_string >= 'A' && *c_string <= 'F')
    {
        uc_ret = (oal_uint8)(*c_string - 'A' + 10);
    }
    else if (*c_string >= 'a' && *c_string <= 'f')
    {
        uc_ret = (oal_uint8)(*c_string - 'a' + 10);
    }

    return uc_ret;
}

/*****************************************************************************
 �� �� ��  : oal_strtoaddr
 ��������  : �ַ���תMAC��ַ
 �������  : pc_param: MAC��ַ�ַ���, ��ʽ xx:xx:xx:xx:xx:xx  �ָ���֧��':'��'-'
 �������  : puc_mac_addr: ת����16���ƺ��MAC��ַ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��26��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_strtoaddr(const oal_int8 *pc_param, oal_uint8 *puc_mac_addr)
{
    oal_uint8   uc_char_index;

    /* ��ȡmac��ַ,16����ת�� */
    for (uc_char_index = 0; uc_char_index < 12; uc_char_index++)
    {
        if ((':' == *pc_param) || ('-' == *pc_param))
        {
            pc_param++;
            if (0 != uc_char_index)
            {
                uc_char_index--;
            }

            continue;
        }

        puc_mac_addr[uc_char_index/2] =
        (oal_uint8)(puc_mac_addr[uc_char_index/2] * 16 * (uc_char_index % 2) +
                                        oal_strtohex(pc_param));
        pc_param++;
    }

}

/*****************************************************************************
 �� �� ��  : oal_memcmp
 ��������  : compare memory areas
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��7��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int  oal_memcmp(OAL_CONST oal_void *p_buf1, OAL_CONST oal_void *p_buf2, oal_uint32 ul_count)
{
    return OAL_MEMCMP(p_buf1, p_buf2, ul_count);
}

OAL_STATIC OAL_INLINE oal_int  oal_strncmp(OAL_CONST oal_int8 *p_buf1, OAL_CONST oal_int8 *p_buf2, oal_uint32 ul_count)
{
    return OAL_STRNCMP(p_buf1, p_buf2, ul_count);
}

/*****************************************************************************
 �� �� ��  : oal_get_random
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_get_random(oal_void)
{
    /* TBD */
    return 1;
}

/*****************************************************************************
 �� �� ��  : oal_gen_random
 ��������  : ���������
 �������  : ul_val:�������   us_rst_flag:0:������������ӣ���0:�����������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��25��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_gen_random(oal_uint32 ul_val, oal_uint8 us_rst_flag)
{
    OAL_STATIC oal_uint32 ul_rand = 0;
    if (0 != us_rst_flag)
    {
        ul_rand = ul_val;
    }
    ul_rand = ul_rand * 1664525L + 1013904223L;
	return (oal_uint8) (ul_rand >> 24);
}

/*****************************************************************************
 �� �� ��  : oal_bit_get_num_one_byte
 ��������  : ��ȡ���ֽ��е�bit1�ĸ���
 �������  : uc_byte:��Ҫ�������ֽ�
 �������  : ��
 �� �� ֵ  : bit�ĸ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��24��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_bit_get_num_one_byte(oal_uint8 uc_byte)
{

    uc_byte = (uc_byte & 0x55) + ((uc_byte >> 1) & 0x55);
    uc_byte = (uc_byte & 0x33) + ((uc_byte >> 2) & 0x33);
    uc_byte = (uc_byte & 0x0F) + ((uc_byte >> 4) & 0x0F);

    return uc_byte;
}

/*****************************************************************************
 �� �� ��  : oal_bit_get_num_four_byte
 ��������  : ��ȡ4�ֽ���bit1�ĸ���
 �������  : uc_byte:��Ҫ�������ֽ�
 �������  : ��
 �� �� ֵ  : bit�ĸ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��24��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_bit_get_num_four_byte(oal_uint32 ul_byte)
{
    ul_byte = (ul_byte & 0x55555555) + ((ul_byte >>  1) & 0x55555555);
    ul_byte = (ul_byte & 0x33333333) + ((ul_byte >>  2) & 0x33333333);
    ul_byte = (ul_byte & 0x0F0F0F0F) + ((ul_byte >>  4) & 0x0F0F0F0F);
    ul_byte = (ul_byte & 0x00FF00FF) + ((ul_byte >>  8) & 0x00FF00FF);
    ul_byte = (ul_byte & 0x0000FFFF) + ((ul_byte >> 16) & 0x0000FFFF);

    return ul_byte;
}

/*****************************************************************************
 �� �� ��  : oal_bit_set_bit_one_byte
 ��������  : ��1�ֽڵ�ָ��λ��һ
 �������  : puc_byte: Ҫ����λ�����ı�����ַ
             nr: ��λ��λ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��24��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_bit_set_bit_one_byte(oal_uint8 *puc_byte, oal_bitops nr)
{
    *puc_byte |= ((oal_uint8)(1 << nr));
}

/*****************************************************************************
 �� �� ��  : oal_bit_clear_bit_one_byte
 ��������  : ��1�ֽڵ�ָ��λ����
 �������  : puc_byte: Ҫ����λ�����ı�����ַ
             nr: �����λ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��24��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_bit_clear_bit_one_byte(oal_uint8 *puc_byte, oal_bitops nr)
{
    *puc_byte &=(~((oal_uint8)(1 << nr)));
}

/*****************************************************************************
 �� �� ��  : oal_bit_set_bit_four_byte
 ��������  : ��4�ֽڵ�ָ��λ��һ
 �������  : pul_byte: Ҫ����λ�����ı�����ַ
             nr: ��λ��λ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��24��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_bit_set_bit_four_byte(oal_uint32 *pul_byte, oal_bitops nr)
{
    *pul_byte |= ((oal_uint32)(1 << nr));
}

/*****************************************************************************
 �� �� ��  : oal_bit_clear_bit_four_byte
 ��������  : ��4�ֽڵ�ָ��λ����
 �������  : pul_byte: Ҫ����λ�����ı�����ַ
             nr: �����λ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��24��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_bit_clear_bit_four_byte(oal_uint32 *pul_byte, oal_bitops nr)
{
    *pul_byte &= ~((oal_uint32)(1 << nr));
}

/*****************************************************************************
 �� �� ��  : oal_bit_set_bit_eight_byte
 ��������  : ��8�ֽڵ�ָ��λ��һ
 �������  : oal_uint64 *pull_byte
             oal_bitops nr
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��26��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_bit_set_bit_eight_byte(oal_uint64 *pull_byte, oal_bitops nr)
{
    *pull_byte |= ((oal_uint64)1 << nr);
}

/*****************************************************************************
 �� �� ��  : oal_bit_clear_bit_eight_byte
 ��������  : ��8�ֽڵ�ָ��λ��0
 �������  : oal_uint64 *pull_byte
             oal_bitops nr
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��26��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_bit_clear_bit_eight_byte(oal_uint64 *pull_byte, oal_bitops nr)
{
    *pull_byte &= ~((oal_uint64)1 << nr);
}

/*****************************************************************************
 �� �� ��  : oal_bit_find_first_bit_one_byte
 ��������  : �ҵ�1�ֽ�������һ����1��λ��
 �������  : puc_byte: Ҫ���ҵ��ֽ�
 �������  : ��
 �� �� ֵ  : ������һ����1��λ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��24��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_bit_find_first_bit_one_byte(oal_uint8 uc_byte)
{
    oal_uint8 uc_ret = 0;

    uc_byte = uc_byte & (-uc_byte);

    while (uc_byte != 1)
    {
        uc_ret++;
        uc_byte = (uc_byte >> 1);

        if (uc_ret > 7)
        {
            return uc_ret;
        }
    }

    return uc_ret;
}

/*****************************************************************************
 �� �� ��  : oal_bit_find_first_zero_one_byte
 ��������  : �ҵ�1�ֽ�������һ����0��λ��
 �������  : puc_byte: Ҫ���ҵ��ֽ�
 �������  : ��
 �� �� ֵ  : ������һ����0��λ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��24��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_bit_find_first_zero_one_byte(oal_uint8 uc_byte)
{
    oal_uint8 uc_ret = 0;

    uc_byte = ~uc_byte;
    uc_byte = uc_byte & (-uc_byte);

    while (uc_byte != 1)
    {
        uc_ret++;
        uc_byte = (uc_byte >> 1);

        if (uc_ret > 7)
        {
            return uc_ret;
        }
    }

    return uc_ret;
}

/*****************************************************************************
 �� �� ��  : oal_bit_find_first_bit_four_byte
 ��������  : �ҵ�1�ֽ�������һ����1��λ��
 �������  : puc_byte: Ҫ���ҵ��ֽ�
 �������  : ��
 �� �� ֵ  : ������һ����1��λ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��24��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_bit_find_first_bit_four_byte(oal_uint32 ul_byte)
{
    oal_uint8 uc_ret = 0;

    if (0 == ul_byte)
    {
        return uc_ret;
    }

    if (!(ul_byte & 0xffff))
    {
        ul_byte >>= 16;
        uc_ret += 16;
    }

    if (!(ul_byte & 0xff))
    {
        ul_byte >>= 8;
        uc_ret += 8;
    }

    if (!(ul_byte & 0xf))
    {
        ul_byte >>= 4;
        uc_ret += 4;
    }

    if (!(ul_byte & 3))
    {
        ul_byte >>= 2;
        uc_ret += 2;
    }

    if (!(ul_byte & 1))
    {
        uc_ret += 1;
    }

    return uc_ret;
}

/*****************************************************************************
 �� �� ��  : oal_bit_find_first_zero_four_byte
 ��������  : �ҵ�1�ֽ�������һ����0��λ��
 �������  : puc_byte: Ҫ���ҵ��ֽ�
 �������  : ��
 �� �� ֵ  : ������һ����0��λ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��24��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_bit_find_first_zero_four_byte(oal_uint32 ul_byte)
{
    oal_uint8 uc_ret = 0;

    ul_byte = ~ul_byte;

    if (!(ul_byte & 0xffff))
    {
        ul_byte >>= 16;
        uc_ret += 16;
    }

    if (!(ul_byte & 0xff))
    {
        ul_byte >>= 8;
        uc_ret += 8;
    }

    if (!(ul_byte & 0xf))
    {
        ul_byte >>= 4;
        uc_ret += 4;
    }

    if (!(ul_byte & 3))
    {
        ul_byte >>= 2;
        uc_ret += 2;
    }

    if (!(ul_byte & 1))
    {
        uc_ret += 1;
    }

    return uc_ret;
}

/*****************************************************************************
 �� �� ��  : oal_set_mac_addr
 ��������  : ���ڶ���mac��ַ ��ֵ��diyimac��ַ
 �������  : puc_mac_addr1: ��һ��mac��ַ
             puc_mac_addr2: �ڶ���mac��ַ
 �������  : ��
 �� �� ֵ  : �ɹ�OAL_SUCC��ʧ��OAL_ERR_CODE_PTR_NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��31��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_set_mac_addr(oal_uint8 *puc_mac_addr1, oal_uint8 *puc_mac_addr2)
{
    puc_mac_addr1[0] = puc_mac_addr2[0];
    puc_mac_addr1[1] = puc_mac_addr2[1];
    puc_mac_addr1[2] = puc_mac_addr2[2];
    puc_mac_addr1[3] = puc_mac_addr2[3];
    puc_mac_addr1[4] = puc_mac_addr2[4];
    puc_mac_addr1[5] = puc_mac_addr2[5];
}

/*****************************************************************************
 �� �� ��  : oal_set_mac_addr_zero
 ��������  : mac��ַ����
 �������  : puc_mac_addr: �������mac��ַ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_set_mac_addr_zero(oal_uint8 *puc_mac_addr)
{
    puc_mac_addr[0] = 0;
    puc_mac_addr[1] = 0;
    puc_mac_addr[2] = 0;
    puc_mac_addr[3] = 0;
    puc_mac_addr[4] = 0;
    puc_mac_addr[5] = 0;
}

/*****************************************************************************
 �� �� ��  : oal_compare_mac_addr
 ��������  : �Ƚ�����mac��ַ�Ƿ����
 �������  : puc_mac_addr1: ��һ��mac��ַ
             puc_mac_addr2: �ڶ���mac��ַ
 �������  : ��
 �� �� ֵ  : ���ȷ���1 �� ��ȷ���0
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��31��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_compare_mac_addr(oal_uint8 *puc_mac_addr1, oal_uint8 *puc_mac_addr2)

{
    return (puc_mac_addr1[0] ^ puc_mac_addr2[0]) | (puc_mac_addr1[1] ^ puc_mac_addr2[1])
    | (puc_mac_addr1[2] ^ puc_mac_addr2[2]) | (puc_mac_addr1[3] ^ puc_mac_addr2[3])
    | (puc_mac_addr1[4] ^ puc_mac_addr2[4]) | (puc_mac_addr1[5] ^ puc_mac_addr2[5]);
}

/*****************************************************************************
 �� �� ��  : oal_cmp_seq_num
 ��������  : �Ƚ������������������ж�˳��ŵĴ�С��seq_num1����seq_num2������
 �������  : (1)��ֵ1
             (2)��ֵ2
             (3)������ֵ�������ֵ
 �������  : ��
 �� �� ֵ  : OAL_TRUE����OAL_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��17��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  oal_cmp_seq_num(
                oal_uint32   ul_seq_num1,
                oal_uint32   ul_seq_num2,
                oal_uint32   ul_diff_value)
{
    if (((ul_seq_num1 < ul_seq_num2) && ((ul_seq_num2 - ul_seq_num1) < ul_diff_value))
       ||((ul_seq_num1 > ul_seq_num2) && ((ul_seq_num1- ul_seq_num2) > ul_diff_value)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : oal_strcmp
 ��������  : �ַ����Ƚ�
 �������  : pc_src: Դ�ַ���
             pc_dst: Ŀ���ַ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��14��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32 oal_strcmp(const oal_int8 *pc_src, const oal_int8 *pc_dst)
{
    oal_int8  c_c1;
    oal_int8  c_c2;
    oal_int32 l_ret = 0;

    do
    {
        c_c1 = *pc_src++;
        c_c2 = *pc_dst++;
        l_ret = c_c1 - c_c2;
        if (l_ret)
        {
            break;
        }
    }while (c_c1);

    return l_ret;
}

/*****************************************************************************
 �� �� ��  : oal_strim
 ��������  : ȥ���ַ�����ʼ���β�Ŀո�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��12��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int8 *oal_strim(oal_int8 *pc_s)
{
    oal_uint32 ul_size;
    oal_int8  *pc_end;

    while (' ' == *pc_s)
    {
        ++pc_s;
    }

    ul_size = OAL_STRLEN(pc_s);
    if (!ul_size)
    {
        return pc_s;
    }

    pc_end = pc_s + ul_size - 1;
    while (pc_end >= pc_s && ' ' == *pc_end)
    {
        pc_end--;
    }

    *(pc_end + 1) = '\0';

    return pc_s;
}

/*****************************************************************************
 �� �� ��  : oal_strcat
 ��������  : ��dest�ַ�����׷��src�ַ���
 �������  : oal_int8 *dest
             const oal_int8 *src
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_int8  *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��6��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int8  *oal_strcat(oal_int8 *dest, const oal_int8 *src)
{
    oal_int8   *pc_tmp;

    pc_tmp = dest;

    while (*dest)
    {
        dest++;
    }

    while ((*dest++ = *src++) != '\0')
    {
        ; //do nothing
    }

    return pc_tmp;
}

/*****************************************************************************
 �� �� ��  : oal_strncat
 ��������  : ��dest�ַ�����src�����ָ�������ַ�
 �������  : oal_int8 *dest
             const oal_int8 *src
             oal_int32 l_cnt
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_int8  *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��6��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int8  *oal_strncat(oal_int8 *dest, const oal_int8 *src, oal_int32 l_cnt)
{
    oal_int8   *pc_tmp;

    pc_tmp = dest;

    if (l_cnt <= 0)
    {
        return pc_tmp;
    }

    while (*dest)
    {
        dest++;
    }

    while ((*dest++ = *src++) != '\0')
    {
        if (--l_cnt == 0)
        {
            *dest = '\0';
            break;
        }
    }

    return pc_tmp;
}

/*****************************************************************************
 �� �� ��  : oal_strstr
 ��������  : ��pc_s1�в���pc_s2��һ�γ��ֵ�λ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��10��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int8*  oal_strstr(oal_int8 *pc_s1, oal_int8 *pc_s2)
{
    return OAL_STRSTR(pc_s1, pc_s2);
}


/*****************************************************************************
 �� �� ��  : oal_init_lut
 ��������  : ��ʼ�������LUT BITMAP��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��27��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_init_lut(oal_uint8  *puc_lut_index_table, oal_uint8 uc_bmap_len)
{
    oal_uint8   uc_lut_idx;

    for (uc_lut_idx = 0; uc_lut_idx < uc_bmap_len; uc_lut_idx++)
    {
        puc_lut_index_table[uc_lut_idx] = 0;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oal_get_lut_index
 ��������  : ��LUT index bitmap���У���ȡһ��û�б�ʹ�õ�������û���ҵ��Ļ���
             ���ز����õ�������ʶ(�ǹؼ�·����δ�����Ż�����ʱ������Ż�)
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��27��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_get_lut_index(
                oal_uint8      *puc_lut_index_table,
                oal_uint8       uc_bmap_len,
                oal_uint16      us_max_lut_size,
                oal_uint16      us_start,
                oal_uint16      us_stop)
{
    oal_uint8       uc_byte     = 0;
    oal_uint8       uc_bit      = 0;
    oal_uint8       uc_temp     = 0;
    oal_uint16      us_index    = 0;

    for (uc_byte = 0; uc_byte < uc_bmap_len; uc_byte++)
    {
        uc_temp = puc_lut_index_table[uc_byte];

        for (uc_bit = 0; uc_bit < 8; uc_bit++)
        {
            if (0x0 == (uc_temp & (1 << uc_bit)))
            {
                us_index = (uc_byte * 8 + uc_bit);
                if ((us_index < us_start) || (us_index >= us_stop))
                {
                    continue;
                }
                if (us_index < us_max_lut_size)
                {
                    puc_lut_index_table[uc_byte] |= (oal_uint8)(1 << uc_bit);

                    return (oal_uint8)us_index;
                }
                else
                {
                    return (oal_uint8)us_max_lut_size;
                }
            }
        }
    }

    return (oal_uint8)us_max_lut_size;
}

/*****************************************************************************
 �� �� ��  : oal_del_lut_index
 ��������  : ��LUT index bitmap���У�ɾ��һ��LUT index (ע:%������Ϊ�Ż���)
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��27��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_del_lut_index(oal_uint8 *puc_lut_index_table, oal_uint8 uc_idx)
{
    oal_uint8 uc_byte = uc_idx / 8;
    oal_uint8 uc_bit  = uc_idx % 8;

    puc_lut_index_table[uc_byte] &= ~(oal_uint8)(1 << uc_bit);
}

/*****************************************************************************
 �� �� ��  : oal_get_virt_addr
 ��������  : �����ַת��Ϊ�����ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��1��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32* oal_get_virt_addr(oal_uint32 *pul_phy_addr)
{
    /* ��ָ������ת�� */
    if (OAL_PTR_NULL == pul_phy_addr)
    {
        return pul_phy_addr;
    }

    return (oal_uint32 *)OAL_PHY_TO_VIRT_ADDR((oal_uint)pul_phy_addr);
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_util.h */
