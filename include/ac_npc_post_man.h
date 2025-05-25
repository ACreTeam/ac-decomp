#ifndef AC_NPC_POST_MAN_H
#define AC_NPC_POST_MAN_H

#include "types.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    aPMAN_BIRTH_PLAYER_HOUSE,
    aPMAN_BIRTH_POST_OFFICE,

    aPMAN_BIRTH_NUM
};

typedef struct npc_post_man_actor_s NPC_POST_MAN;
typedef void (*aPMAN_PROC)(NPC_POST_MAN* actor, GAME_PLAY* play);

struct npc_post_man_actor_s {
    NPC_ACTOR npc_class;
    aPMAN_PROC act_proc;
    u8 action;
    u8 next_action;
    u8 post_office_direct;
    s8 delivery_idx;
    s8 move_idx;
    s8 now_idx;
    u8 cull_flag;
    u8 talk_permit;
    u8 talk_type;
    f32 ground_y;
};

extern ACTOR_PROFILE Npc_Post_Man_Profile;

#ifdef __cplusplus
}
#endif

#endif
