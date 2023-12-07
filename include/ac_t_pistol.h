#ifndef AC_T_PISTOL_H
#define AC_T_PISTOL_H

#include "types.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Pistol_Profile;

typedef void (*PISTOL_PROC)(ACTOR*);

typedef struct t_pistol_s{
    TOOLS_ACTOR tools_class;
    PISTOL_PROC proc; 
    int current_id;
}PISTOL_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

