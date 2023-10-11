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
  eEC_DOUZOU_LIGHT = 101,
  eEC_EFFECT_NUM = 126
};

enum {
  eEC_LIGHT_COLOR_DISABLED,
  eEC_LIGHT_COLOR_INCREASING,
  eEC_LIGHT_COLOR_MAXIMUM,
  eEC_LIGHT_COLOR_DECREASING,

  eEC_LIGHT_COLOR_NUM
};

typedef void (*eEC_NAME2EFFECTMAKE_PROC)(int, xyz_t, int, short, GAME*, u16, s16, s16);

typedef int (*eEC_EFFECTLIGHTSTATUS_PROC)(rgba_t*, int*); // returns eEC_LIGHT_COLOR_*

typedef struct effect_control_clip_s {
  /* 0x00 */ eEC_NAME2EFFECTMAKE_PROC effect_make_proc;
  /* 0x04 */ u8 _04[0x3C - 0x04];
  /* 0x3C */ eEC_EFFECTLIGHTSTATUS_PROC effect_light_status;
  /* 0x40 */ void* _40;
  /* 0x44 */ void* _44;
} eEC_EffectControl_Clip_c;

typedef struct effect_control_s EFFECT_CONTROL_ACTOR;

struct effect_control_s {
  ACTOR actor_class;
  eEC_EffectControl_Clip_c clip;
};


extern ACTOR_PROFILE Effect_Control_Profile;

#ifdef __cplusplus
}
#endif

#endif
