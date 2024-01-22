#ifndef AC_T_ZINNIA2_H
#define AC_T_ZINNIA2_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Zinnia2_Profile;

typedef void (*ZINNIA2_PROC)(ACTOR*);

typedef struct t_zinnia2_s {
    TOOLS_ACTOR tools_class;
    ZINNIA2_PROC proc; 
    int current_id;
    
} ZINNIA2_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

