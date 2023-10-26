#ifndef AC_RADIO_H
#define AC_RADIO_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Radio_Profile;

typedef struct radio_actor_s RADIO_ACTOR;
typedef void (*RADIO_PROC)(RADIO_ACTOR*, GAME_PLAY*);

struct radio_actor_s{
    ACTOR actor_class;
    u8 pad[0x2A0 - 0x174];
    RADIO_PROC proc;
    u8 pad2[0x2B4 - 0x2A4];
    int current_action;
    int next_action;
    u8 pad3[0x2DC - 0x2BC];
};

#ifdef __cplusplus
}
#endif

#endif

