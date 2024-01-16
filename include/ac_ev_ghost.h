#ifndef AC_EV_GHOST_H
#define AC_EV_GHOST_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ev_ghost_s EV_GHOST_ACTOR;

struct ev_ghost_s {
  /* 0x000 */ NPC_ACTOR npc_class;
  /* 0x994 */ void* think_proc;
  /* 0x998 */ int msg_no;
  /* 0x99C */ mActor_name_t give_item;
  /* 0x99E */ s16 bye_bye_angle;
  /* 0x9A0 */ u8 bye_bye_timer;
  /* 0x9A1 */ u8 bye_bye_scale_timer;
  /* 0x9A2 */ u8 bye_bye_transparency_delay_timer;
  /* 0x9A3 */ u8 think_act;
  /* 0x9A4 */
};

extern ACTOR_PROFILE Ev_Ghost_Profile;

#ifdef __cplusplus
}
#endif

#endif

