/*
 * sysdefs.h
 *
 *  Created on: Mar 27, 2015
 *      Author: Cody
 */

#ifndef SYSDEFS_H_
#define SYSDEFS_H_


#ifdef __cplusplus
extern "C" {
#endif


//TODO: get std library inclusion
//#include <stdio.h>
//#include <stdint.h>
//#include <stdbool.h>

typedef unsigned char byte_t;

/* Stay compatible with ugly "windows" style for bool */
#define BOOL bool

#ifndef TRUE
  #define TRUE true
#endif

#ifndef FALSE
  #define FALSE false
#endif

/* ASM and inline function placeholders */
#ifndef ASM
  #define ASM __asm volatile
#endif

#ifndef INLINE
  #if __GNUC__ && !__GNUC_STDC_INLINE__
    #define INLINE extern inline
  #else
    #define INLINE inline
  #endif
#endif

/* GCC does not inline any functions when not optimizing unless you specify
   the 'always_inline' attribute for the function */
#ifndef INLINE_POST
  #define INLINE_POST __attribute__((always_inline))
#endif

/* NULL placeholder */
#ifndef NULL
  #define NULL ((void *) 0)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SYSDEFS_H_ */
