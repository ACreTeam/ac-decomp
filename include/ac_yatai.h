#ifndef AC_YATAI_H
#define AC_YATAI_H

#include "types.h"
#include "ac_structure.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Yatai_Profile;

/* sizeof(YATAI_ACTOR) == 0x2DC */
typedef struct actor_yatai_s {
    STRUCTURE_ACTOR structure_class;
} YATAI_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

