/**
    @copyright: Huawei Technologies Co., Ltd. 2016-XXXX. All rights reserved.

    @file: recovery_record.c

    @brief: source file of module-"recovery record".

    @version: 1.0

    @author: QiDechun ID: 216641

    @date: 2016-04-05

    @history:
*/

/*----includes-----------------------------------------------------------------------*/

#include <linux/printk.h>
#include <linux/vmalloc.h>
#include <asm/string.h>
#include <chipset_common/hwbfm/hwbfr/recovery_record.h>
#include <chipset_common/hwbfm/hwbfr/emmc_rw.h>
#include <chipset_common/hwbfm/hwbfr/memory_alloc.h>


/*----local macroes------------------------------------------------------------------*/


/*----local prototypes----------------------------------------------------------------*/

typedef struct recovery_record_param
{
    unsigned char *buf;
    unsigned int buf_size;
    unsigned int part_offset;
    int record_damaged; /* 0 - good, 1 - damaged */
} recovery_record_param_t;


/*----local variables------------------------------------------------------------------*/

static unsigned int s_crc32_table[CRC32_TABLE_ELEMENT_COUNT] = {0};
static unsigned int s_crc32_table_created = 0;
static recovery_record_param_t s_recovery_record_param[RECORD_PARTS_MAX_COUNT];


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/

static int init_local_recovery_record_param(void);
static int read_recovery_record_to_local_buf(void);
static void create_crc32_table(void);
static unsigned int get_crc32(unsigned char *pbuf, unsigned int data_len);
static int verify_recovery_record(void);
static int init_recovery_record_header(void);


/*----function definitions--------------------------------------------------------------*/

static void create_crc32_table(void)
{
    int i = 0;
    unsigned int value = 0;

    for (i = 0; i < CRC32_TABLE_ELEMENT_COUNT; i++)
    {
        int j = 0;

        value = i;
        for (j = 0; j < 8; j++)
        {
            if (value & 1)
            {
                value = (value >> 1) ^ CRC32_MULTINOMIAL_VALUE;
            }
            else
            {
                value >>= 1;
            }
        }

        s_crc32_table[i] = value;
    }
}


static unsigned int get_crc32(unsigned char *pbuf, unsigned int data_len)
{
    unsigned int crc32 = 0UL;
    unsigned int i = 0UL;

    if (NULL == pbuf)
    {
        return (unsigned int)0xFFFFFFFF;
    }

    if (0 == s_crc32_table_created)
    {
        create_crc32_table();
        s_crc32_table_created = 1;
    }

    crc32 = (unsigned int)0xFFFFFFFF;
    for (i = 0; i < data_len; i++)
    {
        crc32 = (crc32 >> 8) ^ s_crc32_table[(crc32 & 0xFF) ^ pbuf[i]];
    }

    return crc32 ^= (unsigned int)0xFFFFFFFF;
}


static int read_recovery_record_to_local_buf(void)
{
    int i = 0;
    int ret = -1;
    int count = sizeof(s_recovery_record_param) / sizeof(s_recovery_record_param[0]);

    for (i = 0; i < count; i++)
    {
        ret = read_emmc_part(RECOVERY_RECORD_FIRST_DEV_PATH, s_recovery_record_param[i].part_offset,
            s_recovery_record_param[i].buf, s_recovery_record_param[i].buf_size);
        if (0 != ret)
        {
            printk("Read part[%s] failed [ret = %d]!\n", RECOVERY_RECORD_FIRST_DEV_PATH, ret);
            ret = read_emmc_part(RECOVERY_RECORD_SECOND_DEV_PATH, s_recovery_record_param[i].part_offset,
                s_recovery_record_param[i].buf, s_recovery_record_param[i].buf_size);
            if (0 != ret)
            {
                printk("Read part[%s] failed [ret = %d]!\n", RECOVERY_RECORD_SECOND_DEV_PATH, ret);
                return -1;
            }
        }
    }

    return ret;
}


static int init_local_recovery_record_param(void)
{
    int i = 0;
    int count = sizeof(s_recovery_record_param) / sizeof(s_recovery_record_param[0]);

    for (i = 0; i < count; i++)
    {
        s_recovery_record_param[i].buf = (unsigned char *)vmalloc(EACH_RECORD_PART_SIZE);
        if (NULL == s_recovery_record_param[i].buf)
        {
            printk("Invalid parameters!\n");
            return -1;
        }
        memset((void *)s_recovery_record_param[i].buf, 0, EACH_RECORD_PART_SIZE);
        s_recovery_record_param[i].buf_size = EACH_RECORD_PART_SIZE;
        s_recovery_record_param[i].part_offset = (0 == i)
            ? (RRECORD_FIRST_PART_OFFSET) : ((1 == i)
            ? (RRECORD_SECOND_PART_OFFSET) : (RRECORD_THIRD_PART_OFFSET));
    }

    return 0;
}


static int init_recovery_record_header(void)
{
    failure_recovery_record_header_t *pheader = NULL;
    unsigned int header_size = (unsigned int)sizeof(failure_recovery_record_header_t);
    int i = 0;
    int ret = -1;
    int count = sizeof(s_recovery_record_param) / sizeof(s_recovery_record_param[0]);

    for (i = 0; i < count; i++)
    {
        pheader = (failure_recovery_record_header_t *)s_recovery_record_param[i].buf;
        memset((void *)pheader, 0, header_size);
        pheader->magic_number = RECOVERY_RECORD_MAGIC_NUMBER;
        pheader->record_count = (s_recovery_record_param[i].buf_size - header_size)
            / sizeof(failure_recovery_record_t);
        pheader->crc32 = get_crc32(s_recovery_record_param[i].buf + (unsigned int)sizeof(pheader->crc32),
            s_recovery_record_param[i].buf_size - (unsigned int)sizeof(pheader->crc32));
        ret = write_emmc_part(RECOVERY_RECORD_FIRST_DEV_PATH,
            s_recovery_record_param[i].part_offset, (char *)s_recovery_record_param[i].buf,
            s_recovery_record_param[i].buf_size);
        if (0 != ret)
        {
            printk("Write part[%s] failed [ret = %d]!\n", RECOVERY_RECORD_FIRST_DEV_PATH, ret);
            ret = write_emmc_part(RECOVERY_RECORD_SECOND_DEV_PATH,
                s_recovery_record_param[i].part_offset, (char *)s_recovery_record_param[i].buf,
                s_recovery_record_param[i].buf_size);
            if (0 != ret)
            {
                printk("Write part[%s] failed [ret = %d]!\n", RECOVERY_RECORD_SECOND_DEV_PATH, ret);
                return -1;
            }
        }
    }

    return 0;
}


static int verify_recovery_record(void)
{
    unsigned int header_size = (unsigned int)sizeof(failure_recovery_record_header_t);
    failure_recovery_record_header_t *pfirst_header = NULL;
    failure_recovery_record_header_t *psecond_header = NULL;
    int ret = -1;
    int i = 0;
    int valid_record_idx = -1;
    int count = sizeof(s_recovery_record_param) / sizeof(s_recovery_record_param[0]);

    /* 1. check the magic number */
    pfirst_header = (failure_recovery_record_header_t *)s_recovery_record_param[0].buf;
    psecond_header = (failure_recovery_record_header_t *)s_recovery_record_param[1].buf;
    if ((RECOVERY_RECORD_MAGIC_NUMBER != pfirst_header->magic_number)
        && (RECOVERY_RECORD_MAGIC_NUMBER != psecond_header->magic_number))
    {
        return init_recovery_record_header();
    }

    /* 2. check the crc32 value */
    for (i = 0; i < count; i++)
    {
        unsigned int local_crc32 = 0x0;
        failure_recovery_record_header_t *pheader = (failure_recovery_record_header_t *)s_recovery_record_param[i].buf;

        local_crc32 = get_crc32(s_recovery_record_param[i].buf + (unsigned int)sizeof(pheader->crc32),
            s_recovery_record_param[i].buf_size - (unsigned int)sizeof(pheader->crc32));
        if (local_crc32 != pheader->crc32)
        {
            printk("CRC check failed! orig_crc32:0x%08x local_crc32: 0x%08x\n",
                pheader->crc32, local_crc32);
            s_recovery_record_param[i].record_damaged = 1;
        }
        else
        {
            s_recovery_record_param[i].record_damaged = 0;
            valid_record_idx = i;
        }
    }

    /* 3. correct recovery record */
    if (valid_record_idx < 0)
    {
        printk("There is no valid recovery record!\n");
        return init_recovery_record_header();
    }

    ret = 0;
    for (i = 0; i < count; i++)
    {
        if (0 != s_recovery_record_param[i].record_damaged)
        {
            memcpy((void *)s_recovery_record_param[i].buf, (void *)s_recovery_record_param[valid_record_idx].buf,
                s_recovery_record_param[valid_record_idx].buf_size);
            ret = write_emmc_part(RECOVERY_RECORD_FIRST_DEV_PATH, s_recovery_record_param[i].part_offset,
                s_recovery_record_param[i].buf, s_recovery_record_param[i].buf_size);
            if (0 != ret)
            {
                ret = write_emmc_part(RECOVERY_RECORD_SECOND_DEV_PATH, s_recovery_record_param[i].part_offset,
                    s_recovery_record_param[i].buf, s_recovery_record_param[i].buf_size);
                if (0 != ret)
                {
                    printk("write recovery record part failed!\n");
                }
            }
        }
    }

    return ret;
}


int create_recovery_record(failure_recovery_record_t *precord)
{
    int i = 0;
    int count = sizeof(s_recovery_record_param) / sizeof(s_recovery_record_param[0]);
    failure_recovery_record_header_t *pheader = NULL;
    unsigned int header_size = (unsigned int)sizeof(failure_recovery_record_header_t);
    unsigned int record_size = (unsigned int)sizeof(failure_recovery_record_header_t);

    for (i = 0; i < count; i++)
    {
        pheader = (failure_recovery_record_header_t *)s_recovery_record_param[i].buf;
        memcpy((void *)(s_recovery_record_param[i].buf + header_size
            + pheader->next_record_idx * record_size), (void *)precord, record_size);
        pheader->boot_fail_count++;
        pheader->next_record_idx++;
        if (pheader->next_record_idx >= pheader->record_count)
        {
            pheader->next_record_idx = 0;
            pheader->last_record_idx = pheader->record_count - 1;
        }
        else
        {
            pheader->last_record_idx = pheader->next_record_idx - 1;
        }
        pheader->crc32 = get_crc32(s_recovery_record_param[i].buf + (unsigned int)sizeof(pheader->crc32),
            s_recovery_record_param[i].buf_size - (unsigned int)sizeof(pheader->crc32));

        /* 1. write herder */
        if (0 != write_emmc_part(RECOVERY_RECORD_FIRST_DEV_PATH,
            s_recovery_record_param[i].part_offset, (char *)pheader, header_size))
        {
            if (0 != write_emmc_part(RECOVERY_RECORD_SECOND_DEV_PATH,
                s_recovery_record_param[i].part_offset, (char *)pheader, header_size))
            {
                printk("Write recovery record header failed!\n");
                return -1;
            }
        }

        /* 2. write record */
        if (0 != write_emmc_part(RECOVERY_RECORD_FIRST_DEV_PATH,
            (char *)(s_recovery_record_param[i].part_offset + header_size
            + (pheader->boot_fail_count - 1) * record_size), (char *)precord, record_size))
        {
            if (0 != write_emmc_part(RECOVERY_RECORD_SECOND_DEV_PATH,
                (char *)(s_recovery_record_param[i].part_offset + header_size
                + (pheader->boot_fail_count - 1) * record_size), (char *)precord, record_size))
            {
                printk("Write recovery record failed!\n");
                return -1;
            }
        }
    }

    return 0;
}


/* this function need not be realized in bootloader, it should be realized in kernel and erecovery */
int renew_recovery_record(failure_recovery_record_t *precord)
{
    int i = 0;
    int ret = -1;
    int valid_record_idx = -1;
    failure_recovery_record_t recovery_record;
    unsigned int header_size = (unsigned int)sizeof(failure_recovery_record_header_t);
    unsigned int record_size = (unsigned int)sizeof(failure_recovery_record_t);
    unsigned int local_crc32 = 0x0;
    bool system_boot_fail_last_time = false;

    /* 1. alloc memory and init the record_parm */
    memset((void *)s_recovery_record_param, 0, sizeof(s_recovery_record_param));
    for (i = 0; i < RECORD_PARTS_MAX_COUNT; i++)
    {
        s_recovery_record_param[i].buf = (unsigned char *)vmalloc(EACH_RECORD_PART_SIZE);
        if (NULL == s_recovery_record_param[i].buf)
        {
            printk("vmalloc failed!\n");
            goto __errexit;
        }
        memset(s_recovery_record_param[i].buf, 0, EACH_RECORD_PART_SIZE);
        s_recovery_record_param[i].buf_size = EACH_RECORD_PART_SIZE;
        s_recovery_record_param[i].part_offset = (0 == i)
            ? (RRECORD_FIRST_PART_OFFSET) : ((1 == i)
            ? (RRECORD_SECOND_PART_OFFSET) : (RRECORD_THIRD_PART_OFFSET));
    }

    /* 2. read  recovery record*/
    for (i = 0; i < RECORD_PARTS_MAX_COUNT; i++)
    {
        ret = read_emmc_part(RECOVERY_RECORD_FIRST_DEV_PATH, s_recovery_record_param[i].part_offset,
            (char *)s_recovery_record_param[i].buf, s_recovery_record_param[i].buf_size);
        if (0 != ret)
        {
            printk("Read [%s] failed![%d]\n", RECOVERY_RECORD_FIRST_DEV_PATH, ret);
            ret = read_emmc_part(RECOVERY_RECORD_SECOND_DEV_PATH, s_recovery_record_param[i].part_offset,
                (char *)s_recovery_record_param[i].buf, s_recovery_record_param[i].buf_size);
            if (0 != ret)
            {
                printk("Read [%s] failed![%d]\n", RECOVERY_RECORD_SECOND_DEV_PATH, ret);
                goto __errexit;
            }
        }
    }

    /* 3. verify recovery record */
    for (i = 0; i < RECORD_PARTS_MAX_COUNT; i++)
    {
        failure_recovery_record_header_t *pheader = (failure_recovery_record_header_t *)s_recovery_record_param[i].buf;

        local_crc32 = get_crc32(s_recovery_record_param[i].buf + (unsigned int)sizeof(pheader->crc32),
            s_recovery_record_param[i].buf_size - (unsigned int)sizeof(pheader->crc32));
        if (local_crc32 != pheader->crc32)
        {
            printk("CRC check failed! orig_crc32:0x%08x local_crc32: 0x%08x\n", pheader->crc32, local_crc32);
            s_recovery_record_param[i].record_damaged = true;
        }
        else
        {
            s_recovery_record_param[i].record_damaged = false;
            valid_record_idx = i;
        }
    }

    /* 4. correct the recovery record */
    if (valid_record_idx < 0)
    {
        printk("There is no valid recovery record!\n");
        goto __errexit;
    }

    for (i = 0; i < RECORD_PARTS_MAX_COUNT; i++)
    {
        if (s_recovery_record_param[i].record_damaged)
        {
            memcpy((void *)s_recovery_record_param[i].buf, (void *)s_recovery_record_param[valid_record_idx].buf,
                s_recovery_record_param[valid_record_idx].buf_size);
        }
    }

    /* 5. update recovery record*/
    for (i = 0; i < RECORD_PARTS_MAX_COUNT; i++)
    {
        failure_recovery_record_header_t *pheader = (failure_recovery_record_header_t *)s_recovery_record_param[i].buf;

        memset((void *)&recovery_record, 0, record_size);
        memcpy((void *)&recovery_record, (void *)(s_recovery_record_param[i].buf + header_size
            + pheader->last_record_idx * record_size), record_size);
        if (BOOT_FAIL_RECOVERY_SUCCESS != recovery_record.recovery_result)
        {
            system_boot_fail_last_time = true;
        }
        recovery_record.recovery_result = precord->recovery_result;
        memcpy((void *)(s_recovery_record_param[i].buf + header_size + pheader->last_record_idx * record_size),
            (void *)&recovery_record, record_size);
        pheader->crc32 = get_crc32(s_recovery_record_param[i].buf + (unsigned int)sizeof(pheader->crc32),
            s_recovery_record_param[i].buf_size - (unsigned int)sizeof(pheader->crc32));
    }

    /* 6. save recovery record */
    ret = 0;
    for (i = 0; i < RECORD_PARTS_MAX_COUNT; i++)
    {
        if (system_boot_fail_last_time || s_recovery_record_param[i].record_damaged)
        {
            ret = write_emmc_part(RECOVERY_RECORD_FIRST_DEV_PATH, s_recovery_record_param[i].part_offset,
                (char *)s_recovery_record_param[i].buf, s_recovery_record_param[i].buf_size);
            if (0 != ret)
            {
                printk("Read [%s] failed![errno: %d]\n", RECOVERY_RECORD_FIRST_DEV_PATH, ret);
                ret = write_emmc_part(RECOVERY_RECORD_SECOND_DEV_PATH, s_recovery_record_param[i].part_offset,
                    (char *)s_recovery_record_param[i].buf, s_recovery_record_param[i].buf_size);
                if (0 != ret)
                {
                    printk("Read [%s] failed![errno: %d]\n", RECOVERY_RECORD_SECOND_DEV_PATH, ret);
                    goto __errexit;
                }
            }
        }
    }

__errexit:
    for (i = 0; i < RECORD_PARTS_MAX_COUNT; i++)
    {
        vfree(s_recovery_record_param[i].buf);
    }

    return ret;
}


int read_recovery_record(failure_recovery_record_t *precord,
    int record_count_to_read,
    int *record_count_actually_read)
{
    int ret = -1;
    unsigned int buf_size = 0;
    unsigned int header_size = (unsigned int)sizeof(failure_recovery_record_header_t);
    unsigned int record_size = (unsigned int)sizeof(failure_recovery_record_t);
    failure_recovery_record_header_t *precord_header = NULL;

    if ((NULL == precord) || (NULL == record_count_actually_read))
    {
        printk("Invalid parameters!\n");
        return -1;
    }

    /* 1. alloc memory for recovery record */
    memset((void *)&s_recovery_record_param, 0, sizeof(s_recovery_record_param));
    ret = init_local_recovery_record_param();
    if (0 != ret)
    {
        printk("init_local_recovery_record_param failed!\n");
        return -1;
    }

    /* 2. read recovery record to local buf */
    ret = read_recovery_record_to_local_buf();
    if (0 != ret)
    {
        printk("read_recovery_record_to_local_buf failed!\n");
        return -1;
    }

    /* 3. init the record_count_actually_read as 0 */
    *record_count_actually_read = 0;

    /* 4. verify the recovery record */
    ret = verify_recovery_record();
    if (0 != ret)
    {
        printk("verify_recovery_record failed!\n");
        return -1;
    }

    /* 5. read recovery record */
    precord_header = (failure_recovery_record_header_t *)s_recovery_record_param[0].buf;
    *record_count_actually_read = (precord_header->boot_fail_count <= record_count_to_read)
        ? (precord_header->boot_fail_count) : (record_count_to_read);
    buf_size = (*record_count_actually_read) * sizeof(failure_recovery_record_t);
    if (precord_header->next_record_idx >= *record_count_actually_read)
    {
        memcpy((void *)precord, (void *)(s_recovery_record_param[0].buf
            + header_size + (precord_header->next_record_idx
            - *record_count_actually_read) * record_size), buf_size);
    }
    else
    {
        if (precord_header->boot_fail_count > precord_header->record_count)
        {
            unsigned int count_in_the_end = *record_count_actually_read - precord_header->next_record_idx;
            unsigned int count_in_the_begin = precord_header->next_record_idx;

            memcpy((void *)precord, (void *)(s_recovery_record_param[0].buf + header_size
                + (precord_header->record_count - count_in_the_end)* record_size), count_in_the_end * record_size);
            memcpy((void *)((char *)precord + count_in_the_end * record_size),
                (void *)(s_recovery_record_param[0].buf + header_size), count_in_the_begin * record_size);
        }
        else
        {
            memcpy((void *)precord, (void *)(s_recovery_record_param[0].buf
                + header_size + (precord_header->next_record_idx
                - *record_count_actually_read) * record_size), buf_size);
        }
    }

    return 0;
}

