#ifndef AC_TOKYOSO_CONTROL_H
#define AC_TOKYOSO_CONTROL_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aTKC_FLAG_RACE_ACTIVE (1 << 10)

typedef struct ac_tokyoso_event_s {
    u8 _00;
    u8 _01;
    u16 flags;
    s16 pos_04[3];
    s16 pos_0A[2][2];
    s16 angle[2];
    s16 pos_16[2];
    u8 _1A[2];
    u8 _1C[2];
} aEv_tokyoso_c;

extern ACTOR_PROFILE Tokyoso_Control_Profile;

#ifdef __cplusplus
}
#endif

#endif
