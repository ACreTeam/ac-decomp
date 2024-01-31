#ifndef AC_LOTUS_H
#define AC_LOTUS_H

#include "types.h"
#include "ac_structure.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Lotus_Profile;
extern ClObjPipe_c pipeinfo;

/* sizeof(LOTUS_ACTOR) == 0x2DC */
typedef struct actor_lotus_s {
    STRUCTURE_ACTOR structure_class;
} LOTUS_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

