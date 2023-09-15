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

extern void PreRender_setup_savebuf(PreRender* render, int arg1, int arg2, int arg3, int arg4, int arg5);
extern void PreRender_init(PreRender* render);
extern void PreRender_setup_renderbuf(PreRender* render, int arg1, int arg2, void* arg3, void* arg4);
extern void PreRender_cleanup(PreRender* render);

#ifdef __cplusplus
}
#endif

#endif
