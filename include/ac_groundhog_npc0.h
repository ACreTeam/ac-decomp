#ifndef AC_GROUNDHOG_NPC0_H
#define AC_GROUNDHOG_NPC0_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct groundhog_npc0_actor_s GROUNDHOG_NPC0_ACTOR;

typedef void (*aGH0_ACT_PROC)(GROUNDHOG_NPC0_ACTOR* actor, GAME_PLAY* play);

struct groundhog_npc0_actor_s {
    NPC_ACTOR npc_class;
    int action;
    int next_action;
    aGH0_ACT_PROC act_proc;
    int now_term;
    int event_idx;
    s16 def_angle;
    int start_kf_pos_randomized;
};

extern ACTOR_PROFILE Groundhog_Npc0_Profile;

#ifdef __cplusplus
}
#endif

#endif
