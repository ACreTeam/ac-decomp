#ifndef AC_EV_SANTA_H
#define AC_EV_SANTA_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"
#include "m_event.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct event_santa_s EVENT_SANTA_ACTOR;

typedef struct santa_talk_data_s {
  int msg_no;
  int talk_act;
} aESNT_talk_data_c;

typedef void(*aESNT_TALK_PROC)(EVENT_SANTA_ACTOR*, GAME_PLAY*);
typedef void (*aESNT_SETUP_TALK_PROC)(EVENT_SANTA_ACTOR*, GAME_PLAY*, int);

struct event_santa_s {
  /* 0x000 */ NPC_ACTOR npc_class;
  /* 0x994 */ int talk_act;
  /* 0x998 */ aESNT_TALK_PROC talk_proc;
  /* 0x99C */ aESNT_SETUP_TALK_PROC setup_talk_proc;
  /* 0x9A0 */ mActor_name_t present;
  /* 0x9A4 */ aESNT_talk_data_c* talk_data_p;
  /* 0x9A8 */ mEv_santa_event_c* event_p;
  /* 0x9AC */ mEv_santa_event_common_c* event_common_p;
};

extern ACTOR_PROFILE Ev_Santa_Profile;

#ifdef __cplusplus
}
#endif

#endif

