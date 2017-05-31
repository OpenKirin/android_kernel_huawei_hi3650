﻿/*!
 *****************************************************************************
 *
 * @File       lst.h
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 * 
 * The contents of this file are subject to the MIT license as set out below.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * Alternatively, the contents of this file may be used under the terms of the 
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above. 
 * 
 * If you wish to allow use of your version of this file only under the terms 
 * of GPL, and not to allow others to use your version of this file under the 
 * terms of the MIT license, indicate your decision by deleting the provisions 
 * above and replace them with the notice and other provisions required by GPL 
 * as set out in the file called "GPLHEADER" included in this distribution. If 
 * you do not delete the provisions above, a recipient may use your version of 
 * this file under the terms of either the MIT license or GPL.
 * 
 * This License is also included in this distribution in the file called 
 * "MIT_COPYING".
 *
 *****************************************************************************/

#ifndef LST_H
#define LST_H

#if defined (__cplusplus)
extern "C" {
#endif


#ifdef LST_INLINE
#define LST_FQUALS inline static
#else
#ifdef LST_FQUALS
#undef LSTFQUALS
#endif
#define LST_FQUALS
#endif

/* Macro definitions */

#define  LST_LINK LST_LINKAGE_T LST_link

/* Type definitions */

typedef void **LST_LINKAGE_T; /* Private  */


typedef struct
{
    void **first;
    void **last;

} LST_T ; /* Anonymous */


/* Function Prototypes */
LST_FQUALS void   LST_add(LST_T *list, void *item);
LST_FQUALS void   LST_addHead(LST_T *list, void *item);
LST_FQUALS int    LST_empty(LST_T *list);
LST_FQUALS void * LST_first(LST_T *list);
LST_FQUALS void   LST_init(LST_T *list);
LST_FQUALS void * LST_last(LST_T *list);
LST_FQUALS void * LST_next(void *item);
LST_FQUALS void * LST_remove(LST_T *list, void *item);
LST_FQUALS void * LST_removeHead(LST_T *list);
LST_FQUALS int    LST_check(LST_T *list, void *item);


#if defined (__cplusplus)
}
#endif


#ifdef LST_INLINE
#define LST_CINCLUDE
#include "lst.c"
#endif

#endif /* #ifndef LST_H */


