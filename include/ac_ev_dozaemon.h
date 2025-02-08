#ifndef AC_EV_DOZAEMON_H
#define AC_EV_DOZAEMON_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aEDZ_SAVE_FLAG_WAKEUP (1 << 0)
#define aEDZ_SAVE_FLAG_GIVE (1 << 1)
#define aEDZ_SAVE_FLAG_GAVE_FIRST (1 << 2)

enum {
    aEDZ_INIT_PROC_NONE,
    aEDZ_INIT_PROC_NORMAL_WAIT,
    aEDZ_INIT_PROC_TAORERU,
    aEDZ_INIT_PROC_OKIAGARU,
    aEDZ_INIT_PROC_WANDER,

    aEDZ_INIT_PROC_NUM
};

enum {
    aEDZ_THINK_PROC_NONE,
    aEDZ_THINK_PROC_ANIME_NEXT,

    aEDZ_THINK_PROC_NUM
};

enum {
    aEDZ_TALK_PROC_NONE,
    aEDZ_TALK_PROC_NORMAL,
    aEDZ_TALK_PROC_FORCE,

    aEDZ_TALK_PROC_NUM
};

enum {
    aEDZ_THINK_NORMAL_WAIT,
    aEDZ_THINK_TAORERU,
    aEDZ_THINK_OKIAGARU,
    aEDZ_THINK_OKIAGARU_AFTER,
    aEDZ_THINK_WANDER,

    aEDZ_THINK_NUM
};

typedef struct dozaemon_actor_s DOZAEMON_ACTOR;

typedef void (*aEDZ_THINK_PROC)(DOZAEMON_ACTOR* actor, GAME_PLAY* play);
typedef void (*aEDZ_TALK_PROC)(DOZAEMON_ACTOR* actor, GAME_PLAY* play);

struct dozaemon_actor_s {
    NPC_ACTOR npc_class;
    aEDZ_THINK_PROC think_proc;
    aEDZ_TALK_PROC talk_proc;
    s16 give_flag;
    s16 _99E[2];
    u8 think_idx;
    u8 next_think_idx;
    u8 _9A4;
    u8 _9A5;
    u8 change_think;
    u8 melody_backup;
};

extern ACTOR_PROFILE Ev_Dozaemon_Profile;

#ifdef __cplusplus
}
#endif

#endif
