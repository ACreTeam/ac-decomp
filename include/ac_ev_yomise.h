#ifndef AC_EV_YOMISE_H
#define AC_EV_YOMISE_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aEYMS_GOODS_COUNT 8

typedef struct {
    mActor_name_t goods[aEYMS_GOODS_COUNT];
    s16 cnt;
    s16 kind;
} aEv_yomise_save_c;

typedef struct ev_yomise_actor_s EV_YOMISE_ACTOR;

typedef void (*aEYMS_TALK_PROC)(EV_YOMISE_ACTOR* yomise, GAME_PLAY* play);

struct ev_yomise_actor_s {
    NPC_ACTOR npc_class;
    aEYMS_TALK_PROC talk_proc;
    int talk_action;
    int next_talk_action;
    mActor_name_t item;
    s16 cur_choice_start;
    s16 next_choice_start;
    u32 price;
    s16 dst_pos[2];
};

extern ACTOR_PROFILE Ev_Yomise_Profile;

#ifdef __cplusplus
}
#endif

#endif
