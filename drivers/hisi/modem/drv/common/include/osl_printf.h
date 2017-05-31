#ifndef __OSL_PRINTF_H
#define __OSL_PRINTF_H

#ifdef __OS_RTOSCK__
#include <sre_shell.h>
#include <securec.h>
static inline void osl_printf(const CHAR *pcFormat, ...)
{
	va_list arglist;
	char  buf_trans_temp[255+1] = {0};
	int fmt_len =0;

	va_start(arglist, pcFormat);/* [false alarm]:fortify  */
	 /*lint -save -e830 -e539 -e661*/
	fmt_len = vsnprintf_s(buf_trans_temp, 255, 255, pcFormat, arglist);
	va_end(arglist);/* [false alarm]:fortify  */

	if(fmt_len < 0)
	{}
	else if(fmt_len > 255)
	{
		buf_trans_temp[255] = '\0';
		(void)printf("input string too long:%s ...\n",buf_trans_temp);
	}
	else
	{
		buf_trans_temp[fmt_len] = '\0';/* [false alarm]:fortify  */
		(void)printf("%s",buf_trans_temp);
	}
}
#endif

#endif
