#ifndef AC_T_REI2_H
#define AC_T_REI2_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Rei2_Profile;

typedef void (*REI2_PROC)(ACTOR*);

typedef struct t_rei2_s {
    TOOLS_ACTOR tools_class;
    REI2_PROC proc; 
    int current_id;
    
} REI2_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

