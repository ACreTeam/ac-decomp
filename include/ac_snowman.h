#ifndef AC_SNOWMAN_H
#define AC_SNOWMAN_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct snowman_actor_s {
  ACTOR actor_class;
  ClObjPipe_c _174;
  int _190;
  ACTOR* head_actor_p;
  xyz_t _198;
  u8 _1A4[0x1C4 - 0x1A4];
  xyz_t snowball_scale;
  f32 normalized_scale; /* normalized ball scale, [0, 1.0f] */
  f32 _1D4;
  f32 ball_scale; /* [0, 6400.0f] */
  f32 _1DC;
  int scale_result;
  int msg_info;
  int snowman_part;
  s_xyz head_vec;
  u8 _1F2[0x1F8 - 0x1F2];
  s16 unk_1F8;
  u8 _1FA[0x2];
} SNOWMAN_ACTOR;

extern ACTOR_PROFILE Snowman_Profile;

#ifdef __cplusplus
}
#endif

#endif

