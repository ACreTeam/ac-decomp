#ifndef AC_TAMAIRE_NPC0_H
#define AC_TAMAIRE_NPC0_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    aTMN0_THINK_BIRTH,
    aTMN0_THINK_TEAM0_TURN,
    aTMN0_THINK_TEAM0_MOVE,
    aTMN0_THINK_TEAM0_TURN2,
    aTMN0_THINK_TEAM0_KANSEN,
    aTMN0_THINK_TEAM1_TURN,
    aTMN0_THINK_TEAM1_MOVE,
    aTMN0_THINK_TEAM1_TURN2,
    aTMN0_THINK_TEAM1_KANSEN,

    aTMN0_THINK_NUM
};

typedef struct tamaire_npc0_actor_s TAMAIRE_NPC0_ACTOR;

typedef void (*aTMN0_THINK_PROC)(TAMAIRE_NPC0_ACTOR* actor, GAME_PLAY* play);
typedef void (*aTMN0_TALK_PROC)(TAMAIRE_NPC0_ACTOR* actor, GAME_PLAY* play);

struct tamaire_npc0_actor_s {
    NPC_ACTOR npc_class;
    aTMN0_THINK_PROC think_proc;
    aTMN0_TALK_PROC talk_proc;
    s16 timer;
    s16 yasiro_pos[2];
    s16 move_pos[2];
    u8 think_idx;
    u8 next_think_idx;
    u8 move_think_idx;
    u8 talk_idx;
    u8 change_flag;
};

extern ACTOR_PROFILE Tamaire_Npc0_Profile;

#ifdef __cplusplus
}
#endif

#endif
