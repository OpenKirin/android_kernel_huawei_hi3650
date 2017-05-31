

#include "ufshcd.h"
#include "ufs_quirks.h"
#ifdef CONFIG_HISI_BOOTDEVICE
#include <linux/bootdevice.h>
#endif

#define SERIAL_NUM_SIZE 12

static struct ufs_card_fix ufs_fixups[] = {
	/* UFS cards deviations table */
	END_FIX};

static void ufs_set_sec_unique_number(struct ufs_hba *hba,
				      uint8_t *str_desc_buf,
				      uint8_t *desc_buf)
{
	int i;
	uint8_t snum_buf[SERIAL_NUM_SIZE + 1];

	memset(&hba->unique_number, 0, sizeof(hba->unique_number));
	memset(snum_buf, 0, sizeof(snum_buf));

	switch (hba->manufacturer_id) {
	case UFS_VENDOR_SAMSUNG:
		/* samsung has 12Byte long of serail number, just copy it */
		memcpy(snum_buf, str_desc_buf + QUERY_DESC_HDR_SIZE, 12);
		break;
	case UFS_VENDOR_HYNIX:
		/* hynix only have 6Byte, add a 0x00 before every byte */
		for (i = 0; i < 6; i++) {
			snum_buf[i * 2] = 0x0;
			snum_buf[i * 2 + 1] =
				str_desc_buf[QUERY_DESC_HDR_SIZE + i];
		}
		break;
	case UFS_VENDOR_TOSHIBA:
		
		for (i = 0; i < 10; i++) {
			snum_buf[i] =
				str_desc_buf[QUERY_DESC_HDR_SIZE + i * 2 + 1];
		}
		snum_buf[10] = 0;
		snum_buf[11] = 0;
		break;
	default:
		dev_err(hba->dev, "unknown ufs manufacturer id\n");
		break;
	}

	hba->unique_number.manufacturer_id = hba->manufacturer_id;
	hba->unique_number.manufacturer_date = hba->manufacturer_date;
	memcpy(hba->unique_number.serial_number, snum_buf, SERIAL_NUM_SIZE);
}

static int ufs_get_device_info(struct ufs_hba *hba,
			       struct ufs_card_info *card_data)
{
	int err;
	uint8_t model_index;
	uint8_t serial_num_index;
	uint8_t str_desc_buf[QUERY_DESC_STRING_MAX_SIZE + 1];
	uint8_t desc_buf[QUERY_DESC_DEVICE_MAX_SIZE];
	bool ascii_type;

	err = ufshcd_read_device_desc(hba, desc_buf,
				      QUERY_DESC_DEVICE_MAX_SIZE);
	if (err)
		goto out;

	/*
	 * getting vendor (manufacturerID) and Bank Index in big endian
	 * format
	 */
	card_data->wmanufacturerid = desc_buf[DEVICE_DESC_PARAM_MANF_ID] << 8 |
				     desc_buf[DEVICE_DESC_PARAM_MANF_ID + 1];

	hba->manufacturer_id = card_data->wmanufacturerid;

	/*
	 * getting (manufacturer DATE) and Bank Index in big endian
	 * format
	 */
	card_data->wmanufacturer_date =
	    desc_buf[DEVICE_DESC_PARAM_MANF_DATE] << 8 |
	    desc_buf[DEVICE_DESC_PARAM_MANF_DATE + 1];

	hba->manufacturer_date = card_data->wmanufacturer_date;

	/*product name*/
	model_index = desc_buf[DEVICE_DESC_PARAM_PRDCT_NAME];

	memset(str_desc_buf, 0, QUERY_DESC_STRING_MAX_SIZE);
	err = ufshcd_read_string_desc(hba, model_index, str_desc_buf,
				      QUERY_DESC_STRING_MAX_SIZE, ASCII_STD);
	if (err)
		goto out;

	str_desc_buf[QUERY_DESC_STRING_MAX_SIZE] = '\0';
	strlcpy(card_data->model, (str_desc_buf + QUERY_DESC_HDR_SIZE),
		min_t(uint8_t, str_desc_buf[QUERY_DESC_LENGTH_OFFSET],
		      MAX_MODEL_LEN));
	/* Null terminate the model string */
	card_data->model[MAX_MODEL_LEN] = '\0';

	serial_num_index = desc_buf[DEVICE_DESC_PARAM_SN];
	memset(str_desc_buf, 0, QUERY_DESC_STRING_MAX_SIZE);

	/*spec is unicode but sec use hex data*/
	ascii_type = UTF16_STD;

	err = ufshcd_read_string_desc(hba, serial_num_index, str_desc_buf,
				      QUERY_DESC_STRING_MAX_SIZE, ascii_type);

	if (err)
		goto out;
	str_desc_buf[QUERY_DESC_STRING_MAX_SIZE] = '\0';

	ufs_set_sec_unique_number(hba, str_desc_buf, desc_buf);

#ifdef CONFIG_HISI_BOOTDEVICE
	if (get_bootdevice_type() == BOOT_DEVICE_UFS) {
		u32 cid[4];
		int i;
		memcpy(cid, (u32 *)&hba->unique_number, sizeof(cid));
		for (i = 0; i < 3; i++)
			cid[i] = be32_to_cpu(cid[i]);

		cid[3] = (((cid[3]) & 0xffff) << 16) | (((cid[3]) >> 16) & 0xffff);
		set_bootdevice_cid((u32 *)cid);
		set_bootdevice_product_name(card_data->model, MAX_MODEL_LEN);
		set_bootdevice_manfid(hba->manufacturer_id);
	}
#endif

out:
	return err;
}

void ufs_advertise_fixup_device(struct ufs_hba *hba)
{
	int err;
	struct ufs_card_fix *f;
	struct ufs_card_info card_data;

	card_data.wmanufacturerid = 0;
	card_data.model = kzalloc(MAX_MODEL_LEN + 1, GFP_KERNEL);
	if (!card_data.model)
		goto out;

	/* get device data*/
	err = ufs_get_device_info(hba, &card_data);
	if (err) {
		dev_err(hba->dev, "%s: Failed getting device info\n", __func__);
		goto out;
	}

	for (f = ufs_fixups; f->quirk; f++) {
		/* if same wmanufacturerid */
		if (((f->card.wmanufacturerid == card_data.wmanufacturerid) ||
		     (f->card.wmanufacturerid == UFS_ANY_VENDOR)) &&
		    /* and same model */
		    (STR_PRFX_EQUAL(f->card.model, card_data.model) ||
		     !strcmp(f->card.model, UFS_ANY_MODEL)))
			/* update quirks */
			hba->dev_quirks |= f->quirk;
	}
out:
	kfree(card_data.model);
}

void ufs_get_geometry_info(struct ufs_hba *hba)
{
	int err;
	uint8_t desc_buf[QUERY_DESC_GEOMETRY_MAZ_SIZE];
	u64 total_raw_device_capacity;

	err =
	    ufshcd_read_geometry_desc(hba, desc_buf, QUERY_DESC_GEOMETRY_MAZ_SIZE);
	if (err) {
		dev_err(hba->dev, "%s: Failed getting geometry info\n", __func__);
		goto out;
	}
	total_raw_device_capacity =
		(u64)desc_buf[GEOMETRY_DESC_TOTAL_DEVICE_CAPACITY + 0] << 56 |
		(u64)desc_buf[GEOMETRY_DESC_TOTAL_DEVICE_CAPACITY + 1] << 48 |
		(u64)desc_buf[GEOMETRY_DESC_TOTAL_DEVICE_CAPACITY + 2] << 40 |
		(u64)desc_buf[GEOMETRY_DESC_TOTAL_DEVICE_CAPACITY + 3] << 32 |
		(u64)desc_buf[GEOMETRY_DESC_TOTAL_DEVICE_CAPACITY + 4] << 24 |
		(u64)desc_buf[GEOMETRY_DESC_TOTAL_DEVICE_CAPACITY + 5] << 16 |
		(u64)desc_buf[GEOMETRY_DESC_TOTAL_DEVICE_CAPACITY + 6] << 8 |
		desc_buf[GEOMETRY_DESC_TOTAL_DEVICE_CAPACITY + 7] << 0;

#ifdef CONFIG_HISI_BOOTDEVICE
	set_bootdevice_size(total_raw_device_capacity);
#endif

out:
	return;
}

void ufs_get_device_health_info(struct ufs_hba *hba)
{
	int err;
	uint8_t desc_buf[QUERY_DESC_HEALTH_MAX_SIZE];
	u8 pre_eol_info;
	u8 life_time_est_typ_a;
	u8 life_time_est_typ_b;

	err =
	    ufshcd_read_device_health_desc(hba, desc_buf, QUERY_DESC_HEALTH_MAX_SIZE);
	if (err) {
		dev_err(hba->dev, "%s: Failed getting device health info\n", __func__);
		goto out;
	}

	pre_eol_info = desc_buf[HEALTH_DEVICE_DESC_PARAM_PREEOL];
	life_time_est_typ_a = desc_buf[HEALTH_DEVICE_DESC_PARAM_LIFETIMEA];
	life_time_est_typ_b = desc_buf[HEALTH_DEVICE_DESC_PARAM_LIFETIMEB];

#ifdef CONFIG_HISI_BOOTDEVICE
	set_bootdevice_pre_eol_info(pre_eol_info);
	set_bootdevice_life_time_est_typ_a(life_time_est_typ_a);
	set_bootdevice_life_time_est_typ_b(life_time_est_typ_b);
#endif

out:
	return;
}
