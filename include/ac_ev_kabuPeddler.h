#ifndef AC_EV_KABUPEDDLER_H
#define AC_EV_KABUPEDDLER_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aEKPD_KABU_TYPE_NUM 4

typedef struct ev_kabuPeddler_s EV_KABUPEDDLER_ACTOR;

typedef void (*aEKPD_PROC)(EV_KABUPEDDLER_ACTOR*, GAME_PLAY*);
typedef void (*aEKPD_SETUP_PROC)(EV_KABUPEDDLER_ACTOR*, GAME_PLAY*, int);

struct ev_kabuPeddler_s {
    NPC_ACTOR npc_class;
    int kabu_type;
    int talk_act;
    aEKPD_PROC talk_proc;
    aEKPD_SETUP_PROC setup_talk_proc;
};

extern ACTOR_PROFILE Ev_KabuPeddler_Profile;

#ifdef __cplusplus
}
#endif

#endif

