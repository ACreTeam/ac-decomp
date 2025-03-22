#ifndef AC_EV_ARTIST_H
#define AC_EV_ARTIST_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ev_artist_actor_s EV_ARTIST_ACTOR;

typedef void (*aEART_SETUP_ACT_PROC)(EV_ARTIST_ACTOR* artist, GAME_PLAY* play, int action);
typedef void (*aEART_TALK_PROC)(EV_ARTIST_ACTOR* artist, GAME_PLAY* play);

struct ev_artist_actor_s {
    NPC_ACTOR npc_class;
    int action;
    aEART_TALK_PROC talk_proc;
    aEART_SETUP_ACT_PROC setupAction_proc;
    mActor_name_t present;
    mActor_name_t received_item;
};

extern ACTOR_PROFILE Ev_Artist_Profile;

#ifdef __cplusplus
}
#endif

#endif
