

typedef struct _capability {
	unsigned int tag;
	void *value;
	unsigned int type_size;
	unsigned int count;
} cis_capability;

typedef struct _cis_priv_t {
	unsigned int idx;
	unsigned int nr_lane;
	unsigned int cur_expo_line;
	unsigned int cur_vts;
	unsigned int cur_gain;
	cis_capability *caps;
	unsigned int caps_count;
	char group_hold;

	unsigned int shift;
	unsigned int lines;
	unsigned int d_gain_h;
	unsigned int d_gain_l;
	unsigned int a_gain;
	unsigned int fi_manual_flag;
	/* unused varible */
	unsigned int vc_img;
	unsigned int vc_stats;
	unsigned int prepllck_vt_div;
	unsigned int pll_vt_mpy;
	unsigned int vtsyck_div;
	unsigned int vtpxck_div;
	/* added for cut version */
	unsigned char version;
} cis_priv_t;