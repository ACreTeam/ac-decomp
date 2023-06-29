#ifndef AC_MY_HOUSE_H
#define AC_MY_HOUSE_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct actor_my_house_s MY_HOUSE_ACTOR;

struct actor_my_house_s {
  ACTOR actor_class;
  int _174;
  cKF_SkeletonInfo_R_c keyframe;
  int _1E8;
  s_xyz work_area[15];
  s_xyz morph_area[15];
  u8 _2A0[0x2B0 - 0x2A0];
  int door_rotation_speed_idx;
  int house_no;
  int house_shape;
  int _2BC;
  int _2C0;
  int intro_flag;
  f32 door_pos_x;
  f32 door_poz_z;
  f32 door_rotation_speed;
  f32 _2D4;
  int season;
};

extern ACTOR_PROFILE MyHouse_Profile;

#ifdef __cplusplus
}
#endif

#endif

