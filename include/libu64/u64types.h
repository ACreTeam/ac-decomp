#ifndef U64TYPES_H
#define U64TYPES_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  u32 r:8;
  u32 g:8;
  u32 b:8;
  u32 a:8;
} rgba8888_t;

typedef union {
  u32 rgba8888;
  rgba8888_t c;
} rgba8888;

typedef union {
    struct {
        u8 r, g, b, a;
    };
    u32 rgba;
} Color_RGBA8_u32;

#ifdef __cplusplus
}
#endif

#endif
