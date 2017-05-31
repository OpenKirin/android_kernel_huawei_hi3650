#ifndef __VDEC_ADAPTER_H__
#define __VDEC_ADAPTER_H__

#define MAX_PIPES 3

/*!
******************************************************************************
 Structure that defines core properties.
 @brief Core properties
******************************************************************************/
typedef struct {
    unsigned int core_rev;
    unsigned int pvdec_core_id;
    unsigned int mmu_config0;
    unsigned int mmu_config1;
    unsigned int pixel_pipe_cfg[MAX_PIPES];
    unsigned int pixel_misc_cfg[MAX_PIPES];
    unsigned int pixel_max_frame_cfg;
} vxd_core_props;

/*!
******************************************************************************

 @Function              tee_vxd_verify_firmware

 @Description

 This function takes firmware from an unsecured input buffer and puts it into
 a secured buffer. In the middle signature checking/decryption can be performed.
 To be implemented by vendor.

 @Input    non_sec_fw_buf : Physical address of the input buffer in non-secure memory
                            where firmware binary is stored.
                            This buffer can consist of "extra data", carrying
                            signature/cypher information.
 @Input    sec_fw_buf     : Physical address of the output buffer in secure memory
                            where firmware binary should be placed.
 @Input    fw_blob_size   : Size (in bytes) of the input buffer (firmware blob).
 @Output   fw_core_size   : Size (in bytes) of the firmware core module which has to be
                            uploaded into the MTX RAM.

 @Return   This function returns either TRUE or FALSE.

******************************************************************************/
unsigned int tee_vxd_verify_firmware(unsigned long long non_sec_fw_buf,
                                     unsigned long long sec_fw_buf,
                                     unsigned int fw_blob_size,
                                     unsigned int *fw_core_size);

/*!
******************************************************************************

 @Function              tee_vxd_power_on

 @Description

 This function turns on core clocks, read core capabilities and uploads firmware
 to the MTX.

 NOTE: The above routines can cause delay of up to few seconds.

 @Input    ptd              : Page table directory physical address needed to
                              configure MMU, before uploading firmware.
 @Input    sec_fw_buff_virt : Device virtual address of a buffer in the secure
                              memory containing verified/decrypted firmware binary.
 @Input    fw_core_size     : Size (in bytes) of the firmware core module which
                              has to be uploaded into the MTX RAM.
 @Output   props            : Structure containing properties and capabilities
                              of the hardware decoder.

 @Return   This function returns either TRUE or FALSE.

******************************************************************************/
unsigned int tee_vxd_power_on(unsigned long long ptd,
                              unsigned long sec_fw_buff_virt,
                              unsigned int fw_core_size,
                              vxd_core_props *props);

/*!
******************************************************************************

 @Function              tee_vxd_power_off

 @Description

 This function turns off core clocks.

 @Return   None
******************************************************************************/
void tee_vxd_power_off(void);

#endif

