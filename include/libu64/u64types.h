#ifndef U64TYPES_H
#define U64TYPES_H

#include "types.h"

typedef struct xyz_s {
  f32 x, y, z;
} xyz_t;

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

#endif
