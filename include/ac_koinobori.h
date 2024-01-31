#ifndef AC_KOINOBORI_H
#define AC_KOINOBORI_H

#include "types.h"
#include "ac_structure.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Koinobori_Profile;

/* sizeof(KOINOBORI_ACTOR) == 0x2DC */
typedef struct actor_koinobori_s{
    STRUCTURE_ACTOR structure_class;
} KOINOBORI_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

