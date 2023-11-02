#ifndef AC_TAMA_H
#define AC_TAMA_H

#include "types.h"
#include "m_actor.h"
#include "ac_structure.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tama_actor_s {
  STRUCTURE_ACTOR structure_class;
} TAMA_ACTOR;

extern ACTOR_PROFILE Tama_Profile;

#ifdef __cplusplus
}
#endif

#endif

