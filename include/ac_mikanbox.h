#ifndef AC_MIKANBOX_H
#define AC_MIKANBOX_H

#include "types.h"
#include "m_actor.h"
#include "ac_mikanbox_clip.h"
#include "ac_structure.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mikanbox_actor_s {
    STRUCTURE_ACTOR s_actor;
} MIKANBOX_ACTOR;

extern ACTOR_PROFILE Mikanbox_Profile;  

#ifdef __cplusplus
}
#endif

#endif
