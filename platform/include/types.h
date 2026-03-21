/* Shadow: replaces root-level include/types.h for arm64.
 * Fixes s32/u32 (long → int32_t), size_t, and removes MSL_C PPC-specific math. */
#ifndef TYPES_H
#define TYPES_H

#include "platform/compat.h"  /* fixed-width typedefs: s8..s64, u8..u64, f32, f64 */
#include <stddef.h>            /* size_t */
#include <math.h>              /* sqrtf, etc. — replaces MSL_C/w_math.h */

/* size_t might be defined as unsigned long in compat.h via stddef.h; ensure u32 compat */
#ifndef _SIZE_T_DEF
#define _SIZE_T_DEF
/* size_t is from <stddef.h> — already defined */
#endif

typedef volatile u8  vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;
typedef volatile s8  vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;
typedef volatile f32 vf32;
typedef volatile f64 vf64;

typedef unsigned int uint;
typedef void*        unkptr;
typedef u32          unknown;

/* Include the original macros section (FRAMERATE_ADJ etc.) */
#include "macros.h"

/* Alignment and utility macros from original types.h */
#define ALIGN_PREV(u, align)  ((u) & (~((align) - 1)))
#define ALIGN_NEXT(u, align)  (((u) + ((align) - 1)) & (~((align) - 1)))
#define IS_ALIGNED(X, N)      (((X) & ((N) - 1)) == 0)
#define IS_NOT_ALIGNED(X, N)  (((X) & ((N) - 1)) != 0)

#define FLAG_ON(V, F)         (((V) & (F)) == 0)
#define FLAG_OFF(V, F)        (((V) & (F)) != 0)

#define BUTTON_NONE   0x0000
#define BUTTON_CRIGHT 0x0001
#define BUTTON_CLEFT  0x0002
#define BUTTON_CDOWN  0x0004
#define BUTTON_CUP    0x0008
#define BUTTON_R      0x0010
#define BUTTON_L      0x0020
#define BUTTON_X      0x0040
#define BUTTON_Y      0x0080
#define BUTTON_DRIGHT 0x0100
#define BUTTON_DLEFT  0x0200
#define BUTTON_DDOWN  0x0400
#define BUTTON_DUP    0x0800
#define BUTTON_START  0x1000
#define BUTTON_Z      0x2000
#define BUTTON_B      0x4000
#define BUTTON_A      0x8000

#define FRAMES_PER_SECOND 60
#define FRAMES_PER_MINUTE (FRAMES_PER_SECOND * 60)

#define ARRAY_SIZE(arr, type) (sizeof(arr) / sizeof(type))
#define ARRAY_COUNT(arr)      ((int)(sizeof(arr) / sizeof((arr)[0])))

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define FLOOR(n, f) (((n) / (f)) * (f))

#define F32_IS_ZERO(v) (fabsf(v) < 0.008f)

#define DECREMENT_TIMER(timer) ((timer) == 0 ? 0 : --(timer))

#define ARGB8_to_RGB5A3(argb8) \
    ((u16)(((argb8) & 0xFF000000) >= 0xE0000000 \
           ? (0x8000 | ((((argb8) >> 16) & 0xF8) << 7) | ((((argb8) >> 8) & 0xF8) << 2) | (((argb8) & 0xFF) >> 3)) \
           : ((((argb8) >> 24) & 0xE0) << 7) | ((((argb8) >> 16) & 0xF0) << 4) | (((argb8) >> 8) & 0xF0) | (((argb8) & 0xF0) >> 4)))

#define GPACK_RGB5A3(r, g, b, a) \
    ARGB8_to_RGB5A3((((a) & 0xFF) << 24) | (((r) & 0xFF) << 16) | (((g) & 0xFF) << 8) | ((b) & 0xFF))

/* Metrowerks-specific attributes — no-ops on Clang/GCC */
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#define FORCESTRIP
#define MATCH_FORCESTRIP
#define ORDER_BSS_DATA
#define BSS_ORDER_GROUP_START
#define BSS_ORDER_GROUP_END
#define BSS_ORDER_ITEM(v)

#define VER_GAFE01_00 0
#define VER_GAFU01_00 1

#if VERSION == VER_GAFU01_00
#define FRAMERATE_ADJ(n) (((n) * 60) / 50)
#define FRAMERATE_TIMER(n) (((n) * 50) / 60)
#define FRAMERATE_SELECT(f60, f50) (f50)
#else
#define FRAMERATE_ADJ(n) (n)
#define FRAMERATE_TIMER(n) (n)
#define FRAMERATE_SELECT(f60, f50) (f60)
#endif

#endif /* TYPES_H */
