#ifndef AC_T_HAT3_H
#define AC_T_HAT3_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Hat3_Profile;

typedef void (*HAT3_PROC)(ACTOR*);

typedef struct t_hat3_s{
    TOOLS_ACTOR tools_class;
    HAT3_PROC proc; 
    int current_id;
}HAT3_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

