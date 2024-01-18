#ifndef AC_FIELD_DRAW_H
#define AC_FIELD_DRAW_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aFD_BLOCK_DRAW_NUM 9

typedef struct field_draw_s FIELD_DRAW_ACTOR;

typedef struct field_draw_block_s {
  xyz_t wpos;
  int bx;
  int bz;
  int exist;
} aFD_block_c;

typedef struct field_draw_marin_info_s {
  u32 tile0_scroll;
  u32 tile1_scroll;
  rgba_t beach_env_color;
  u32 frame;
} aFD_marin_info_c;

struct field_draw_s {
  ACTOR actor_class;
  aFD_block_c block[aFD_BLOCK_DRAW_NUM];
  aFD_marin_info_c marin_info;
};

extern ACTOR_PROFILE Field_Draw_Profile;

#ifdef __cplusplus
}
#endif

#endif

