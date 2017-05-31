

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#ifndef offsetof
#define offsetof(s, m) ((unsigned int)&(((s *)0)->m))
#endif

#ifndef array_count
#define array_count(x) (sizeof(x) / sizeof(x[0]))
#endif

#ifndef max
#define max(x, y) ((x) > (y) ? (x) : (y))
#endif

#ifndef min
#define min(x, y) ((x) > (y) ? (y) : (x))
#endif

#if RELEASE_VERSION
#define ASSERT(x)
#else
#define ASSERT(x) (if (!(x)) \
	{ \
	loge("[%s]: ASSERT Failed.", #x); \
	__asm__ __volatile__("swi  0"); \
	})
#endif

#endif /*UTILS_H_INCLUDED */
