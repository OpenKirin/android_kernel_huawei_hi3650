/**
    @copyright: Huawei Technologies Co., Ltd. 2016-XXXX. All rights reserved.

    @file: emmc_rw.h

    @brief: header file of module-"emmc read write".

    @version: 1.0

    @author: QiDechun ID: 216641

    @date: 2016-04-05

    @history:
*/

#ifndef EMMC_RW_H
#define EMMC_RW_H


/*----includes-----------------------------------------------------------------------*/


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/


/*----export prototypes---------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/

int read_emmc_part(const char *part_name, unsigned long long offset, char *buf, unsigned long long buf_size);
int write_emmc_part(const char *part_name, unsigned long long offset, char *buf, unsigned long long buf_size);

#ifdef __cplusplus
}
#endif

#endif /* EMMC_RW_H */

