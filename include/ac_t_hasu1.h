#ifndef AC_T_HASU1_H
#define AC_T_HASU1_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Hasu1_Profile;

typedef void (*HASU1_PROC)(ACTOR*);

typedef struct t_hasu1_s{
    TOOLS_ACTOR tools_class;
    HASU1_PROC proc; 
    int current_id;
}HASU1_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

