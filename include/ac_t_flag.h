#ifndef AC_T_FLAG_H
#define AC_T_FLAG_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Flag_Profile;

typedef struct t_flag_s{
    TOOLS_ACTOR tools_class;
    s16 angle;
    s16 addendedang;
    int unk1D0;
    xyz_t work;
}FLAG_ACTOR;


#ifdef __cplusplus
}
#endif

#endif

