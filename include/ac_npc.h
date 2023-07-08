#ifndef AC_NPC_H
#define AC_NPC_H

#include "types.h"
#include "m_actor.h"
#include "m_play.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ac_npc_clip_s aNPC_Clip_c;

typedef int (*aNPC_SETUP_ACTOR_PROC)(GAME_PLAY*, mActor_name_t, s8, int, s16, int, int, int, int);

struct ac_npc_clip_s {
  aNPC_SETUP_ACTOR_PROC setupActor_proc;
  void* _004[(0x12C - 0x004) / sizeof(void*)];
};

extern ACTOR_PROFILE Npc_Profile;

#ifdef __cplusplus
}
#endif

#endif

