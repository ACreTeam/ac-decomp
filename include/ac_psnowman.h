#ifndef AC_PSNOWMAN_H
#define AC_PSNOWMAN_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(PSNOWMAN_ACTOR) == 0x198 */
typedef struct actor_p_snowman_s {
  /* 0x000 */ ACTOR actor_class;
  /* 0x174 */ int current_id;
  /* 0x178 */ int message_num;
  /* 0x17C */ f32 head;
  /* 0x180 */ f32 head_scale;
  /* 0x184 */ f32 body;
  /* 0x188 */ f32 body_scale;
  /* 0x18C */ f32 eye_heigth;
  /* 0x190 */ f32 speed;
  /* 0x194 */ s16 head_angle;
} PSNOWMAN_ACTOR;

extern ACTOR_PROFILE Psnowman_Profile;

#ifdef __cplusplus
}
#endif

#endif

