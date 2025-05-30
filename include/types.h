#ifndef TYPES_H
#define TYPES_H

#include "MSL_C/w_math.h"
#include <dolphin/types.h>
#include "macros.h"

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
#ifndef _SIZE_T_DEF
#define _SIZE_T_DEF
typedef unsigned long size_t;
#endif
typedef unsigned long long u64;
typedef unsigned int uint;

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;
typedef volatile s8 vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

typedef float f32;
typedef double f64;
typedef volatile f32 vf32;
typedef volatile f64 vf64;

typedef int BOOL;

// Pointer to unknown, to be determined at a later date.
typedef void* unkptr;
typedef u32 unknown;

#define TRUE 1
#define FALSE 0

#ifndef NULL
#ifndef __cplusplus
#define NULL ((void*)0)
#else
#define NULL 0
#endif
#endif
#define nullptr 0

// #ifdef __MWERKS__
// #define AT_ADDRESS(x) : (x)
// #else
// #define AT_ADDRESS(x) __attribute__((section(".data." #x)))
// #endif

#define ALIGN_PREV(u, align) (u & (~(align - 1)))
#define ALIGN_NEXT(u, align) ((u + (align - 1)) & (~(align - 1)))
#define IS_ALIGNED(X, N) (((X) & ((N) - 1)) == 0)
#define IS_NOT_ALIGNED(X, N) (((X) & ((N) - 1)) != 0)

#define FLAG_ON(V, F) (((V) & (F)) == 0)
#define FLAG_OFF(V, F) (((V) & (F)) != 0)

#ifndef ATTRIBUTE_ALIGN
#if defined(__MWERKS__) || defined(__GNUC__)
#define ATTRIBUTE_ALIGN(num) __attribute__((aligned(num)))
#elif defined(_MSC_VER)
#define ATTRIBUTE_ALIGN(num)
#else
#error unknown compiler
#endif
#endif

#define BUTTON_NONE 0x0000
#define BUTTON_CRIGHT 0x0001
#define BUTTON_CLEFT 0x0002
#define BUTTON_CDOWN 0x0004
#define BUTTON_CUP 0x0008
#define BUTTON_R 0x0010
#define BUTTON_L 0x0020
#define BUTTON_X 0x0040
#define BUTTON_Y 0x0080
#define BUTTON_DRIGHT 0x0100
#define BUTTON_DLEFT 0x0200
#define BUTTON_DDOWN 0x0400
#define BUTTON_DUP 0x0800
#define BUTTON_START 0x1000
#define BUTTON_Z 0x2000
#define BUTTON_B 0x4000
#define BUTTON_A 0x8000

#define FRAMES_PER_SECOND 60
#define FRAMES_PER_MINUTE (FRAMES_PER_SECOND * 60)

#define ARRAY_SIZE(arr, type) (sizeof(arr) / sizeof(type))
#define ARRAY_COUNT(arr) (int)(sizeof(arr) / sizeof(arr[0]))

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define FLOOR(n, f) (((n) / (f)) * (f))

#define F32_IS_ZERO(v) (fabsf(v) < 0.008f)

#define DECREMENT_TIMER(timer) ((timer) == 0 ? 0 : --(timer))

/* ARGB8 color format (32 bits) to RGB5A3 color format (16 bits) */
#define ARGB8_to_RGB5A3(argb8)                                                                                     \
    ((u16)(((argb8) & 0xFF000000) >= 0xE0000000                                                                    \
               ? /* Fully opaque, 5 bits per color channel */ (0x8000 | ((((argb8) >> 16) & 0xF8) << 7) |          \
                                                               ((((argb8) >> 8) & 0xF8) << 2) |                    \
                                                               (((argb8) & 0xFF) >> 3))                            \
               : /* 3 bits of transparency, 4 bits per color channel */ (                                          \
                     ((((argb8) >> 24) & 0xE0) << 7) | ((((argb8) >> 16) & 0xF0) << 4) | (((argb8) >> 8) & 0xF0) | \
                     (((argb8) & 0xF0) >> 4))))

#define GPACK_RGB5A3(r, g, b, a) \
    ARGB8_to_RGB5A3((((a) & 0xFF) << 24) | (((r) & 0xFF) << 16) | (((g) & 0xFF) << 8) | ((b) & 0xFF))

#pragma section RX "forcestrip"
#ifndef __INTELLISENSE__
#define FORCESTRIP __declspec(section "forcestrip")
#else
#define FORCESTRIP
#endif

#if defined(MUST_MATCH) && defined(__MWERKS__)
#define MATCH_FORCESTRIP FORCESTRIP
#else
#define MATCH_FORCESTRIP
#endif

#if !defined(__INTELLISENSE__) && defined(MUST_MATCH)
#define ORDER_BSS_DATA static asm void order_bss()
#define ORDER_BSS(s) lis r3, s @ha
#define BSS_ORDER_GROUP_START FORCESTRIP ORDER_BSS_DATA {
#define BSS_ORDER_GROUP_END }
#define BSS_ORDER_ITEM(v) ORDER_BSS(v)
#else
#define BSS_ORDER_GROUP_START
#define BSS_ORDER_GROUP_END
#define BSS_ORDER_ITEM(v)
#endif

#ifndef __cplusplus
// Some definitions rely on wchar_t being defined
typedef unsigned short wchar_t;
#endif

// #if DEBUG
// #define ASSERTLINE(line, cond) \
//     ((cond) || (OSPanic(__FILE__, line, "Failed assertion " #cond), 0))

// #define ASSERTMSGLINE(line, cond, msg) \
//     ((cond) || (OSPanic(__FILE__, line, msg), 0))

// // This is dumb but we dont have a Metrowerks way to do variadic macros in the macro to make this done in a not scrubby way.
// #define ASSERTMSG1LINE(line, cond, msg, arg1) \
//     ((cond) || (OSPanic(__FILE__, line, msg, arg1), 0))
    
// #define ASSERTMSG2LINE(line, cond, msg, arg1, arg2) \
//     ((cond) || (OSPanic(__FILE__, line, msg, arg1, arg2), 0))

// #define ASSERTMSGLINEV(line, cond, ...) \
//     ((cond) || (OSPanic(__FILE__, line, __VA_ARGS__), 0))

// #else
// #define ASSERTLINE(line, cond) (void)0
// #define ASSERTMSGLINE(line, cond, msg) (void)0
// #define ASSERTMSG1LINE(line, cond, msg, arg1) (void)0
// #define ASSERTMSG2LINE(line, cond, msg, arg1, arg2) (void)0
// #define ASSERTMSGLINEV(line, cond, ...) (void)0
// #endif

#endif
