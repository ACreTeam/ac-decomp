#ifndef MACROS_H
#define MACROS_H

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define CLAMP(low, high, x) \
    ((x) > (high) ? (high) : ((x) < (low) ? (low) : (x)))

#define ROUND_UP(x, align) (((x) + (align)-1) & (-(align)))
#define ROUND_UP_PTR(x, align) \
    ((void *)((((u32)(x)) + (align)-1) & (~((align)-1))))

#define ROUND_DOWN(x, align) ((x) & (-(align)))
#define ROUND_DOWN_PTR(x, align) ((void *)(((u32)(x)) & (~((align)-1))))

#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#define STRING_SIZE(x) (sizeof(x) - 1) // for char arrays, subtract 1 to act as null terminator?

#define CLEAR_PATH(x) __memclr((x), sizeof((x)))

#define ALIGN(x) __attribute__((aligned(x)))
#ifndef ATTRIBUTE_ALIGN
#define ATTRIBUTE_ALIGN(x) __attribute__((aligned(x)))
#endif
#ifdef __MWERKS__
#ifndef DECL_SECTION
#define DECL_SECTION(x) __declspec(section x)
#endif
#ifndef DECL_WEAK
#define DECL_WEAK __declspec(weak)
#endif
#define DONT_INLINE __attribute__((never_inline))
#else
#ifndef DECL_SECTION
#define DECL_SECTION(x)
#endif
#ifndef DECL_WEAK
#define DECL_WEAK __attribute__((weak))
#endif
#define DONT_INLINE __attribute__((noinline))
#endif

// Align X to the previous N bytes (N must be power of two)
#define ALIGN_PREV(X, N) ((X) & ~((N)-1))
// Align X to the next N bytes (N must be power of two)
#define ALIGN_NEXT(X, N) ALIGN_PREV(((X) + (N)-1), N)
#define IS_ALIGNED(X, N) (((X) & ((N)-1)) == 0)
#define IS_NOT_ALIGNED(X, N) (((X) & ((N)-1)) != 0)

#define READU32_BE(ptr, offset) \
    (((u32)ptr[offset] << 24) | ((u32)ptr[offset + 1] << 16) | ((u32)ptr[offset + 2] << 8) | (u32)ptr[offset + 3]);

#define FLAG_ON(V, F) (((V) & (F)) == 0)
#define FLAG_OFF(V, F) (((V) & (F)))

// inserts empty bytes for unknown sections in classes/structs
#define PLACEHOLDER_BYTES(start, end) u8 _##start[end - start]

// Codewarrior tricks for matching decomp
// (Functions are given prototypes for -requireprotos)
#ifdef __MWERKS__
// Force BSS order
#define CW_FORCE_BSS(module, ...)    \
    void fake_function(...);         \
    void FORCE_BSS##module##x(void); \
    void FORCE_BSS##module##x(void)  \
    {                                \
        fake_function(__VA_ARGS__);  \
    }
// Force strings into pool
#define CW_FORCE_STRINGS(module, ...) \
    void fake_function(...);          \
    void FORCE_STRINGS##module(void); \
    void FORCE_STRINGS##module(void)  \
    {                                 \
        fake_function(__VA_ARGS__);   \
    }
#define ASM asm
#else
#define CW_FORCE_BSS(module, ...)
#define CW_FORCE_STRINGS(module, ...)
#define ASM
#endif

// For VSCode
#ifdef __INTELLISENSE__
#define asm
#define __attribute__(x)
#define __declspec(x)
#endif

#endif
