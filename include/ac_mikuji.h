#ifndef AC_MIKUJI_H
#define AC_MIKUJI_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct actor_mikuji_s MIKUJI_ACTOR;

typedef void (*MIKUJI_PROC)(MIKUJI_ACTOR*, GAME_PLAY*);

struct actor_mikuji_s{
    ACTOR actor_class;
    u8 pad[0x2A0 - 0x174];
    MIKUJI_PROC proc;
    u8 pad2[0x2B4 - 0x2A4];
    int current_action;
    int next_action;
    u8 pad3[0x2DC - 0x2BC];
};

extern ACTOR_PROFILE Mikuji_Profile;

#ifdef __cplusplus
}
#endif

#endif

