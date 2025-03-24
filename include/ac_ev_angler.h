#ifndef AC_EV_ANGLER_H
#define AC_EV_ANGLER_H

#include "types.h"
#include "m_actor.h"
#include "m_personal_id.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct fish_event_data_s {
    int size;
    PersonalID_c pID;
    s16 pos[2];
    u8 talk_flag;
    u8 flag;
} aEANG_event_data_c;

typedef struct fish_event_common_s {
    u8 foreigner;
} aEANG_event_common_c;

typedef struct ev_angler_actor_s EV_ANGLER_ACTOR;

typedef void (*aEANG_TALK_PROC)(EV_ANGLER_ACTOR* angler, GAME_PLAY* play);
typedef void (*aEANG_SETUP_TALK_PROC)(EV_ANGLER_ACTOR* angler, GAME_PLAY* play, int talk_act);

struct ev_angler_actor_s {
    NPC_ACTOR npc_class;
    int talk_action;
    aEANG_TALK_PROC talk_proc;
    aEANG_SETUP_TALK_PROC setup_talk_proc;
    mActor_name_t item;
    u8 item_idx;
    int size;
};

extern ACTOR_PROFILE Ev_Angler_Profile;

#ifdef __cplusplus
}
#endif

#endif
