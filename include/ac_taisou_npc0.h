#ifndef AC_TAISOU_NPC0_H
#define AC_TAISOU_NPC0_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"
#include "audio.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct taisou_npc0_actor_s {
    NPC_ACTOR npc_class;
    s8 action;
    u8 anim_initialized;
    u8 gymnastic_state;
    u8 delay_cnt;
    Radio_c radio;
    int anime_dir;
    f32 current_ratio;
    int frame;
    mActor_name_t held_item;
    u8 talk_proc;
    u8 talk_state;
    u8 soncho_event;
} TAISOU_NPC0_ACTOR;

extern ACTOR_PROFILE Taisou_Npc0_Profile;

#ifdef __cplusplus
}
#endif

#endif
