#ifndef AC_BOXMANAGER_H
#define AC_BOXMANAGER_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct box_manager_s{
    ACTOR actor_class;
    u8 pad[0x1F8 - 0x174];
}BOXMANAGER_ACTOR;

extern ACTOR_PROFILE BoxManager_Profile;

#ifdef __cplusplus
}
#endif

#endif

