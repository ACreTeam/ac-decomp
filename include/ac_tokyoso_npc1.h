#ifndef AC_TOKYOSO_NPC1_H
#define AC_TOKYOSO_NPC1_H

#include "lb_reki.h"
#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tokyoso_npc1_actor_s TOKYOSO_NPC1_ACTOR;

// TODO: finish this
struct tokyoso_npc1_actor_s {
    NPC_ACTOR npc_class;
    void* think_proc;
    int msg_start_no;
    f32 speed;
    s16 _9A0;
    s16 start_pos[2];
    s16 timer;
    u8 _9A8;
    u8 _9A9;
    u8 _9AA;
    u8 talk_idx;
    u8 _9AC;
};

extern ACTOR_PROFILE Tokyoso_Npc1_Profile;

#ifdef __cplusplus
}
#endif

#endif
