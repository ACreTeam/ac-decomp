#ifndef AC_MIKUJI_H
#define AC_MIKUJI_H

#include "types.h"
#include "ac_structure.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct actor_mikuji_s MIKUJI_ACTOR;

typedef void (*MIKUJI_PROC)(MIKUJI_ACTOR*, GAME_PLAY*);

struct actor_mikuji_s{
    STRUCTURE_ACTOR structure_class;
};

extern ACTOR_PROFILE Mikuji_Profile;

#ifdef __cplusplus
}
#endif

#endif

