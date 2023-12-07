#ifndef AC_T_HAT1_H
#define AC_T_HAT1_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Hat1_Profile;

typedef void (*HAT1_PROC)(ACTOR*);

typedef struct t_hat1_s{
    TOOLS_ACTOR tools_class;
    HAT1_PROC proc; 
    int current_id;
}HAT1_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

