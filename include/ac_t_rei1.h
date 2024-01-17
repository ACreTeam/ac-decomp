#ifndef AC_T_REI1_H
#define AC_T_REI1_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Rei1_Profile;

typedef void (*REI1_PROC)(ACTOR*);

typedef struct t_rei1_s {
    TOOLS_ACTOR tools_class;
    REI1_PROC proc; 
    int current_id;
    
} REI1_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

