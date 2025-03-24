#ifndef AC_EV_BROKER2_H
#define AC_EV_BROKER2_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aEBR2_PRICE_MULT 4

typedef struct ev_broker2_actor_s EV_BROKER2_ACTOR;

typedef void (*aEBR2_PROC)(EV_BROKER2_ACTOR* broker2, GAME_PLAY* play);

struct ev_broker2_actor_s {
    NPC_ACTOR npc_class;
    int action;
    aEBR2_PROC action_proc;
    s16 talk_angle;
    u8 cur_zone;
    u8 next_zone;
    u8 player_zone;
    u8 state;
    s16 player_angle;
    s8 item_idx;
    u8 explain_flag;
    u8 sell_flag;
};

extern ACTOR_PROFILE Ev_Broker2_Profile;

#ifdef __cplusplus
}
#endif

#endif
