#ifndef EF_EFFECT_CONTROL_H
#define EF_EFFECT_CONTROL_H

#include "types.h"
#include "m_lib.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

enum effect_type {
  eEC_EFFECT_SHOCK,
  eEC_EFFECT_DUST,
  eEC_EFFECT_MUKA,
  eEC_EFFECT_WARAU,
  /* TODO: finish */

  eEC_EFFECT_NUM = 126
};

typedef void (*eEC_NAME2EFFECTMAKE_PROC)(int, xyz_t, int, short, GAME*, u16, s16, s16);

typedef struct effect_control_clip_s {
  eEC_NAME2EFFECTMAKE_PROC effect_make_proc;
  /* TODO: finish */
} eEC_EffectControl_Clip_c;

typedef struct effect_control_s EFFECT_CONTROL_ACTOR;

struct effect_control_s {
  ACTOR actor_class;
  eEC_EffectControl_Clip_c clip;
};


#ifdef __cplusplus
}
#endif

#endif
