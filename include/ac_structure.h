#ifndef AC_STRUCTURE_H
#define AC_STRUCTURE_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef ACTOR* (*aSTR_SETUP_ACTOR_PROC)(GAME_PLAY*, mActor_name_t, int, f32, f32);

// TODO: finish clip
typedef struct actor_structure_clip_s {
  aSTR_SETUP_ACTOR_PROC setup_actor_proc;
} aSTR_Clip_c;

#ifdef __cplusplus
}
#endif

#endif
