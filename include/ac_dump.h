#ifndef AC_DUMP_H
#define AC_DUMP_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Dump_Profile;

typedef struct actor_dump_s DUMP_ACTOR;

typedef void (*DUMP_PROC)(DUMP_ACTOR*, GAME_PLAY*);

struct actor_dump_s{
    ACTOR actor_class;
    u8 pad[0x2A0 - 0x174];
    DUMP_PROC proc;
    u8 pad2[0x2B4 - 0x2A4];
    int current_action;
    u8 pad3[0x2D8 - 0x2B8];
    int season;
};

#ifdef __cplusplus
}
#endif

#endif

