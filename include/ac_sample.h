#ifndef AC_SAMPLE_H
#define AC_SAMPLE_H

#include "types.h"
#include "m_actor.h"
#include "m_collision_obj.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sample_actor_s {
  ACTOR actor_class;

  cKF_SkeletonInfo_R_c keyframe;
  s_xyz work_area[8];
  s_xyz morph_area[8];

  ClObjPipe_c stand;
  
  int main_action;
  int draw_action;

  char* obj_bank_ram_start; // maybe unused in AC? was used to exchange data on N64
} SAMPLE_ACTOR;

extern ACTOR_PROFILE Sample_Profile;

#ifdef __cplusplus
}
#endif

#endif
