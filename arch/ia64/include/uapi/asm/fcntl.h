#ifndef _ASM_IA64_FCNTL_H
#define _ASM_IA64_FCNTL_H


#define force_o_largefile()	\
		(personality(current->personality) != PER_LINUX32)

#include <linux/personality.h>
#include <asm-generic/fcntl.h>

#endif /* _ASM_IA64_FCNTL_H */
