#ifndef AC_T_HAT2_H
#define AC_T_HAT2_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Hat2_Profile;

typedef void (*HAT2_PROC)(ACTOR*);

typedef struct t_hat2_s{
    TOOLS_ACTOR tools_class;
    HAT2_PROC proc; 
    int current_id;
}HAT2_ACTOR;


#ifdef __cplusplus
}
#endif

#endif

