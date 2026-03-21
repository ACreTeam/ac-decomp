#pragma once
/* arm64 compatibility layer.
 *
 * The original types.h defines s32/u32 as 'signed/unsigned long', which is
 * 64-bit on arm64.  This shadow header must be included BEFORE dolphin/types.h
 * (achieved by placing platform/include first in the include path) so that
 * stdint.h defines the correct fixed-width aliases before types.h runs.
 *
 * Also fixes uintptr_t: the original defines it as 'unsigned int' (32-bit),
 * but on arm64 pointers are 64-bit.
 */

#include <stdint.h>
#include <stddef.h>

/* Ensure the game's typedef aliases map to the right width on arm64.
 * We redefine them here; the shadow dolphin/types.h includes this file
 * instead of relying on the originals. */
typedef int8_t   s8;
typedef uint8_t  u8;
typedef int16_t  s16;
typedef uint16_t u16;
typedef int32_t  s32;   /* was 'signed long' — 64-bit on arm64 */
typedef uint32_t u32;   /* was 'unsigned long' — 64-bit on arm64 */
typedef int64_t  s64;
typedef uint64_t u64;
typedef float    f32;
typedef double   f64;
typedef char    *Ptr;
/* uintptr_t from stdint.h is the correct platform-sized type */

#ifndef __OBJC__
typedef int BOOL;
#else
/* In Objective-C, BOOL is defined as bool by objc.h — reuse it */
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

/* Metrowerks at-address extension: no-op on all non-Metrowerks compilers */
#define AT_ADDRESS(addr)

#define ATTRIBUTE_ALIGN(num) __attribute__((aligned(num)))

#ifndef INT_MIN
#define INT_MIN (-2147483647 - 1)
#endif
#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void*)0)
#endif
#endif

#ifndef membersize
#define membersize(type, member) (sizeof(((type*)0)->member))
#endif

/* Metrowerks compiler intrinsic — map to standard abs on other compilers */
#ifndef __MWERKS__
#include <stdlib.h>
static inline int __abs(int x) { return x < 0 ? -x : x; }
#endif

/* C++ keywords used in some decompiled C files (compiled as gnu99, not C++) */
#ifndef __cplusplus
#ifndef true
#define true  1
#define false 0
#endif
#endif

/* nullptr: C++ keyword used in some decompiled C files */
#ifndef __cplusplus
#ifndef nullptr
#define nullptr ((void*)0)
#endif
#endif
