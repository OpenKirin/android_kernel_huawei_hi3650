/*
 * sescan.c
 *
 * the sescan.c for selinux status checking
 *
 * Yongzheng Wu <Wu.Yongzheng@huawei.com>
 * likun <quentin.lee@huawei.com>
 * likan <likan82@huawei.com>
 *
 * Copyright (c) 2001-2021, Huawei Tech. Co., Ltd. All rights reserved.
 */

#include "./include/sescan.h"

static const char *TAG = "sescan";

int get_selinux_enforcing(void)
{
	return selinux_enforcing;
}

int sescan_hookhash(uint8_t *hash)
{
	struct scatterlist sg;
	struct hash_desc desc;
	struct security_operations **security_ops;

	security_ops = kallsyms_lookup_name("security_ops");
	if (!security_ops) {
		RSLogError(TAG, "get symbol security_ops addres failed");
		return -EFAULT;
	}

	sg_init_one(&sg, *security_ops,
				(uint)sizeof(struct security_operations));

	desc.flags = 0;
	desc.tfm = crypto_alloc_hash("sha256", 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(desc.tfm)) {
		RSLogError(TAG, "crypto alloc hash error %ld",
							PTR_ERR(desc.tfm));
		return -ENOMEM;
	}
	crypto_hash_init(&desc);
	crypto_hash_update(&desc, &sg,
				(uint)sizeof(struct security_operations));
	crypto_hash_final(&desc, (u8 *)hash);

	crypto_free_hash(desc.tfm);
	return 0;
}
