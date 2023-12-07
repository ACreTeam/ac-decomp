#ifndef AC_T_TUMBLER_H
#define AC_T_TUMBLER_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tool_tumbler_s TOOL_TUMBLER_ACTOR;
typedef void (*aTTB_ACTION_PROC)(TOOL_TUMBLER_ACTOR*);

struct tool_tumbler_s {
  TOOLS_ACTOR tools_class;
  aTTB_ACTION_PROC action_proc;
  int action;
};

extern void aTTB_actor_ct(ACTOR* actorx, GAME* game);
extern void aTTB_actor_move(ACTOR* actorx, GAME* game);
extern void aTTB_actor_draw(ACTOR* actorx, GAME* game);

extern ACTOR_PROFILE T_Tumbler_Profile;

#ifdef __cplusplus
}
#endif

#endif

