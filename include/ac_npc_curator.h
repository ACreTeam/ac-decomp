#ifndef AC_NPC_CURATOR_H
#define AC_NPC_CURATOR_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_curator_actor_s NPC_CURATOR_ACTOR;

struct npc_curator_actor_s {
  NPC_ACTOR npc_class;
  int action;
  aNPC_SUB_PROC action_proc;
  int sleep_wait_timer;
  int talk_act_idx;
  aNPC_SUB_PROC talk_proc;
  aNPC_PROC setupTalkAction_proc;
  int msg_no;
  int _9B0; // might be unused 'awake' state
  mActor_name_t donated_item;
};

extern ACTOR_PROFILE Npc_Curator_Profile;

#ifdef __cplusplus
}
#endif

#endif

