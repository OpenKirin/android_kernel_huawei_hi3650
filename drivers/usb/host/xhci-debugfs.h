

#ifdef CONFIG_DEBUG_FS
int xhci_create_debug_file(struct device *dev);
void xhci_remove_debug_file(void);
#else
static inline int xhci_create_debug_file(struct device *dev)
{
	return 0;
}

static inline void xhci_remove_debug_file(void) { }
#endif

