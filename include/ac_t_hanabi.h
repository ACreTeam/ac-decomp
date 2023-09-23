#ifndef AC_T_HANABI_H
#define AC_T_HANABI_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Hanabi_Profile;

typedef void (*HANABI_PROC)(ACTOR*);

typedef struct t_hanabi_s{
    TOOLS_ACTOR tools_class;
    u8 pad2[0x8];
    HANABI_PROC proc; 
    int current_id;
}HANABI_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

