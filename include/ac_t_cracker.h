#ifndef AC_T_CRACKER_H
#define AC_T_CRACKER_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Cracker_Profile;

typedef void (*CRACKER_PROC)(ACTOR*);

typedef struct t_cracker_s{
    TOOLS_ACTOR tools_class;
    CRACKER_PROC proc; 
    int current_id;
}CRACKER_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

