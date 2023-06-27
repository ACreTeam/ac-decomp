#ifndef PRERENDER_H
#define PRERENDER_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct prerender_s {
  u16 width;
  u16 height;

  u16 width_bak;
  u16 height_bak;

  u8 _08[8];

  void* framebuffer;
  void* framebuffer_bak;

  void* _18;

  int _1C;
  int _20;

  u8 _24[0x24];
} PreRender;

#ifdef __cplusplus
}
#endif

#endif
