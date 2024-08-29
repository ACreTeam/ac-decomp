#ifndef AC_EFFECTBG_H
#define AC_EFFECTBG_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    EffectBG_EFFECT_SHAKE,
    EffectBG_EFFECT_CUT_LEFT,
    EffectBG_EFFECT_CUT_RIGHT,
    EffectBG_EFFECT_SHAKE_SMALL,
    EffectBG_EFFECT_SHAKE_LARGE,

    EffectBG_EFFECT_NUM
};

typedef void (*EffectBG_MAKE_EFFECTBG_PROC)(GAME*, s16, s16, xyz_t*);

extern ACTOR_PROFILE Effectbg_Profile;

#ifdef __cplusplus
}
#endif

#endif
