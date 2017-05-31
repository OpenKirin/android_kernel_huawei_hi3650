

typedef struct _tag_hjpeg_intf hjpeg_intf_t;

typedef struct _tag_hjpeg_vtbl {
    int (*get_name)(hjpeg_intf_t *i);
    int (*encode_process) (hjpeg_intf_t *i, void *cfg);
    int (*power_on) (hjpeg_intf_t *i);
    int (*power_down) (hjpeg_intf_t *i);
    int (*get_reg) (hjpeg_intf_t *i, void* cfg);
    int (*set_reg) (hjpeg_intf_t *i, void* cfg);
}hjpeg_vtbl_t;

typedef struct _tag_hjpeg_intf {
    hjpeg_vtbl_t *vtbl;
} hjpeg_intf_t;

extern int
hjpeg_register(
        struct platform_device* pdev,
        hjpeg_intf_t* si);

extern void
hjpeg_unregister(hjpeg_intf_t* si);


