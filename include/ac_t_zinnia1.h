#ifndef AC_T_ZINNIA1_H
#define AC_T_ZINNIA1_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Zinnia1_Profile;

typedef void (*ZINNIA1_PROC)(ACTOR*);

typedef struct t_zinnia1_s {
    TOOLS_ACTOR tools_class;
    ZINNIA1_PROC proc; 
    int current_id;
    
} ZINNIA1_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

