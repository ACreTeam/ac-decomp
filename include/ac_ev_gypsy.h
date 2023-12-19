#ifndef AC_EV_GYPSY_H
#define AC_EV_GYPSY_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aEGPS_FORTUNE_PRICE 50

typedef struct ev_gypsy_actor_s EV_GYPSY_ACTOR;

typedef void (*aEGPS_TALK_INIT_PROC)(EV_GYPSY_ACTOR*, GAME_PLAY*);
typedef void (*aEGPS_TALK_PROC)(EV_GYPSY_ACTOR*, GAME_PLAY*);
typedef void (*aEGPS_TALK_SETUP_PROC)(EV_GYPSY_ACTOR*, GAME_PLAY*, int);

struct ev_gypsy_actor_s {
  NPC_ACTOR npc_class;
  int talk_action;
  aEGPS_TALK_PROC talk_proc;
  aEGPS_TALK_SETUP_PROC setup_talk_proc;
  int fortune_given;
};

extern ACTOR_PROFILE Ev_Gypsy_Profile;

#ifdef __cplusplus
}
#endif

#endif

