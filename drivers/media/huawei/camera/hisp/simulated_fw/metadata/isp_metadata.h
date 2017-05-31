

#ifndef ISP_METADATA_H_INCLUDED
#define ISP_METADATA_H_INCLUDED
#define ISP_METADATA_LINUX

/************************************************************************/
#ifdef ISP_METADATA_FIRMWARE

#define META_LOGE(fmt, args...) loge(fmt, ##args)
#define META_LOGD(fmt, args...) logd(fmt, ##args)
#define META_LOGI(fmt, args...) logi(fmt, ##args)

#define META_MALLOC os_malloc
#define META_FREE(x) if(os_free(x) != 0) \
                     META_LOGE("%s line %d: os free error", __FUNCTION__, __LINE__);

#define META_EINVAL  ISP_EINVAL
#define META_EPERM   ISP_EPERM
#define META_ENOMEM  ISP_ENOMEM

#include "camera_metadata_tags.h"

#endif
/************************************************************************/

/************************************************************************/

#ifdef ISP_METADATA_ANDROID

#define META_LOGE(fmt, args...) ALOGE(fmt, ##args)
#define META_LOGD(fmt, args...) ALOGD(fmt, ##args)
#define META_LOGI(fmt, args...) ALOGI(fmt, ##args)

#define META_MALLOC malloc
#define META_FREE free

#define META_EINVAL  EINVAL
#define META_EPERM   EPERM
#define META_ENOMEM  ENOMEM

#endif
/************************************************************************/

/************************************************************************/
#ifdef ISP_METADATA_LINUX
#include "camera_metadata_tags.h"
#include <linux/kernel.h>
#define LOG_TAG "META_DATA"
//#define META_LOGE(fmt, args...) printf("[E/" LOG_TAG "]" fmt "\n", ##args)
//#define META_LOGD(fmt, args...) printf("[D/" LOG_TAG "]" fmt "\n", ##args)
//#define META_LOGI(fmt, args...) printf("[I/" LOG_TAG "]" fmt "\n", ##args)

#define META_LOGE(fmt, ...) \
    do { \
            printk("[E/" LOG_TAG "]" fmt "\n", ##__VA_ARGS__); \
    }while (0)

#define META_LOGD(fmt, ...) \
    do { \
            printk("[D/" LOG_TAG "]" fmt "\n", ##__VA_ARGS__); \
    }while (0)

#define META_LOGI(fmt, ...) \
    do { \
            printk("[I/" LOG_TAG "]" fmt "\n", ##__VA_ARGS__); \
    }while (0)

#define META_MALLOC(x) kmalloc(x, GFP_KERNEL)
#define META_FREE kfree

#define META_EINVAL  EINVAL
#define META_EPERM   EPERM
#define META_ENOMEM  ENOMEM

#endif
#define TAG_SIZE (sizeof(uint32_t))
#define ISP_METADATA_SECTION_OFFSET (16)
#define ISP_TAG_ID_MASK (0xFFFF)
#define HEAD_FLAG 0x003EFEFE
#define TOTAL_ENTRY_SIZE 0x2000 /* 8k */
#define MIN_BUFFER_SIZE (sizeof(meta_head_t) + TOTAL_ENTRY_SIZE)
#define ISP_METADATA_BUFFER_SIZE (0x96000)
/************************************************************************/

/* this is size of fw metadata. */
#ifdef   HISP_V150
#include "../hisp150_md_message.h"
#else
#include "../hisp_md_message.h"
#endif

#ifndef MD_PARAM_SIZE
#define MD_PARAM_SIZE  ((sizeof(buffer_md_t))/(4))
#endif

/**
 * @brief: This is a enum type of tag payload data.
 */
enum {
    DATA_BYTE     = 0, /**< Unsigned 8-bit integer (unsigned char)         */
    DATA_INT32    = 1, /**< Signed 32-bit integer (signed int)             */
    DATA_FLOAT    = 2, /**< 32-bit float (float)                           */
    DATA_INT64    = 3, /**< Signed 64-bit integer (signed long long int)   */
    DATA_DOUBLE   = 4, /**< 64-bit float (double)                          */
    DATA_RATIONAL = 5, /**< A 64-bit fraction (camera_metadata_rational_t) */
    NUM_DATA_TYPES     /**< Number of type fields                          */
};

typedef struct camera_rational {
    signed int numerator;
    signed int denominator;
} camera_rational_t;

typedef struct _tag_info
{
    const char* tag_name;
    unsigned int data_type;
    unsigned int data_max_count;
} tag_info_t;

typedef struct isp_metadata{
    void* priv;
}isp_metadata_t;

typedef struct meta_entry
{
    unsigned int  entry_info; //first bit from left indicates tag exist or not,
                              //other bits means the tag's offset in payload section from metadata buffer's very begin.
    unsigned int  data_count;
}meta_entry_t;

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief  Get a tag entry.
 *
 * @param  meta  Point to a isp_metadata_t which contains a metadata buffer.
 * @param  tag   A metadata tag.
 * @param  entry Output, Pointer to a meta_entry_t.
 *
 * @retval int
 */
int isp_metadata_get_tag_entry(isp_metadata_t* meta, unsigned int tag, meta_entry_t* entry);

/**
 * @brief  Get a tag info.
 *
 * @param  tag  A metadata tag.
 *
 * @retval tag_info_t*
 */
const tag_info_t* isp_metadata_get_taginfo(unsigned int tag);

/**
 * @brief  Get a vendor section name of a vendor tag.
 *
 * @param  tag         A metadata vendor tag.
 *
 * @retval const char* String of section name
 */
const char* isp_metadata_get_vendor_section_name(unsigned int tag);

/**
 * @brief  Get count of all vendor tags.
 *
 * @param  void
 *
 * @retval unsigned int Count of all vendor tags.
 */
unsigned int isp_metadata_get_vendor_tag_count(void);

/**
 * @brief  Get all vendor tags.
 *
 * @param  tag_arry An array buffer pointer, that would be filled with all vendor tags.
 *
 * @retval void
 */
void isp_metadata_get_all_vendor_tags(unsigned int *tag_array);

/**
 * @brief  Create a struction of isp_metadata_t that contains the metadata
 *         buffer passed in.If NULL buffer is passed in, isp_metadata_set_buffer
 *         must be called to set a metadata buffer.
 *
 * @param  buffer      A buffer that used to save tags and payload data. Can be NULL.
 * @param  buffer_size Size of metadata buffer.
 *
 * @retval isp_metadata_t*
 */
isp_metadata_t* isp_metadata_create(void* buffer, unsigned int buffer_size);

/**
 * @brief  Destroy a isp_metadata_t. If there's a metadata buffer managed by this
 *         isp_metadata_t, the metadata buffer will not freed with isp_metadata_t.
 *
 * @param  meta      Point to a pointer of isp_metadata_t, and will be setted to NULL if success.
 *
 * @retval void*     Pointer of buffer that managed by the isp_metadata_t.
 */
void* isp_metadata_destroy(isp_metadata_t** meta);

/**
 * @brief  Attach a metadata buffer into a isp_metadata_t. If a metadata buffer is already setted, error
 *         will be returned.
 *
 * @param  meta        Shouldn't be NULL.
 * @param  buffer      A buffer that used to save tags and payload data. Shouldn't be NULL.
 * @param  buffer_size Size of metadata buffer.
 *
 * @retval int
 */
int isp_metadata_attach_buffer(isp_metadata_t* meta, void* buffer, unsigned int buffer_size);

/**
 * @brief  Detach a metadata buffer which managed by this isp_metadata_t. Not to free the buffer.
 *
 * @param  meta      Point to a isp_metadata_t which contains a metadata buffer.
 *
 * @retval void*     Pointer of buffer that managed by the isp_metadata_t.
 */
void* isp_metadata_detach_buffer(const isp_metadata_t* meta);

/**
 * @brief  Set a tag and its payload data into a buffer which managed by the isp_metadata_t.
 *
 * @param  meta      Point to a isp_metadata_t which contains a metadata buffer.
 * @param  tag       A metadata tag.
 * @param  value     Address of the tag's payload data.
 * @param  type_size Size of the payload data's type.
 * @param  count     One tag's payload data may be an array. The count refers to the number of elements.
 *
 * @retval int
 */
int isp_metadata_set(const isp_metadata_t* meta, unsigned int tag, const void* value, unsigned int type_size, unsigned int count);

/**
 * @brief  Get a tag's payload data from a buffer which managed by the isp_metadata_t.
 *
 * @param  meta      Point to a isp_metadata_t which contains a metadata buffer.
 * @param  tag       A metadata tag.
 * @param  result    Address of the result buffer.
 * @param  type_size Size of the payload data's type.
 * @param  count     One tag's payload data may be an array. The count refers to the number of elements.
 *
 * @retval int
 */
int isp_metadata_get(const isp_metadata_t* meta, unsigned int tag, void* result, unsigned int type_size, unsigned int count);

/**
 * @brief  Update metadata from src_meta to des_meta.
 *
 * @param  src_meta  Source metadata.
 * @param  des_meta  Destination metadata.
 *
 * @retval int
 */
int isp_metadata_update(const isp_metadata_t* src_meta, isp_metadata_t* des_meta);

/**
 * @brief  Delete a tag.
 *
 * @param  meta Point to a isp_metadata_t which contains a metadata buffer.
 * @param  tag  Tag to delete.
 *
 * @retval int
 */
int isp_metadata_delete(const isp_metadata_t* meta, unsigned int tag);

/**
 * @brief  Get real tags count that saved in a metadata buffer.
 *
 * @param  meta Point to a isp_metadata_t which contains a metadata buffer.
 *
 * @retval int
 */
unsigned int isp_metadata_get_tags_count(isp_metadata_t* meta);

/**
 * @brief  Get real tags that saved in a metadata buffer.
 *
 * @param  meta       Point to a isp_metadata_t which contains a metadata buffer.
 * @param  tag_array  Output, An array buffer for filling tags.
 * @param  array_size The tag_array buffer size.
 *
 * @retval int
 */
int isp_metadata_get_tags(isp_metadata_t* meta, unsigned int *tag_array, unsigned int array_size);

/**
 * @brief  Get size of tag's type.
 *
 * @param  meta       A metadata tag.
 *
 * @retval int size of type.
 */
unsigned int isp_metadata_get_type_size(unsigned int tag);

/**
 * @brief  Get count of tag data.
 *
 * @param  meta       A metadata tag.
 *
 * @retval int
 */
unsigned int isp_metadata_get_data_count(unsigned int tag);


/**
 * @brief  Dump tag and payload data.
 *
 * @param  meta      Point to a isp_metadata_t which contains a metadata buffer.
 *
 * @retval void
 */
void isp_metadata_dump(const isp_metadata_t* meta);

/**
 * @brief  Get a tag's payload addr in a buffer which managed by the isp_metadata_t.
 *
 * @param  meta      Point to a isp_metadata_t which contains a metadata buffer.
 * @param  tag       A metadata tag.
 *
 * @retval void*
 */
void* isp_metadata_get_data_addr(const isp_metadata_t* meta, unsigned int tag);


#ifdef __cplusplus
};
#endif

#endif /*ISP_METADATA_H_INCLUDED*/

/********************************* END ***********************************************/

