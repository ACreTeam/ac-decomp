#ifndef AC_BOAT_H
#define AC_BOAT_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct boat_s BOAT_ACTOR;

typedef void (*aBT_PROC)(BOAT_ACTOR*, GAME_PLAY*);

struct boat_s {
  ACTOR actor_class;
  int _174;
  cKF_SkeletonInfo_R_c keyframe;
  int _1E8;
  s_xyz work[15];
  s_xyz morph[15];
  aBT_PROC action_proc;
  int _2A4;
  int _2A8;
  int _2AC;
  int _2B0;
  int action;
  int roll_cycle;
  int roll_timer;
  int point;
  int direction;
  f32 _2C8;
  f32 _2CC;
  f32 _2D0;
  f32 rudder;
  int _2D8;
};

extern ACTOR_PROFILE Boat_Profile;

#ifdef __cplusplus
}
#endif

#endif

