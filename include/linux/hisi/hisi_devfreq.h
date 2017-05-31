#ifndef _HISI_DEVFREQ_H
#define _HISI_DEVFREQ_H

int hisi_devfreq_free_freq_table(struct device *dev, unsigned int **table);

int hisi_devfreq_init_freq_table(struct device *dev, unsigned int **table);

#endif /* _HISI_DEVFREQ_H */
