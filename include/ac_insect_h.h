#ifndef AC_INSECT_H_H
#define AC_INSECT_H_H

#include "types.h"
#include "m_actor.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(aINS_Init_c) == 0x18 */
typedef struct insect_init_s {
  /* 0x00 */ int insect_type;
  /* 0x04 */ xyz_t position;
  /* 0x10 */ int extra_data;
  /* 0x14 */ GAME* game;
} aINS_Init_c;

/* sizeof(aINS_INSECT_DUMMY_ACTOR) == 0x288 */
typedef struct insect_dummy_actor_s {
  ACTOR actor;
  /* TODO: finish */
} aINS_INSECT_DUMMY_ACTOR;

typedef aINS_INSECT_DUMMY_ACTOR* (*aINS_make_insect_proc)(aINS_Init_c*, int);
typedef void (*aINS_make_ant_proc)(aINS_Init_c*, s8, s8);
typedef void (*aINS_dt_proc)(ACTOR*, GAME*);
typedef aINS_INSECT_DUMMY_ACTOR* (*aINS_make_actor_proc)(GAME*, int, xyz_t*);
typedef void (*aINS_set_pl_act_tim_proc)(int, int, int);
typedef int (*aINS_chk_live_insect_proc)(int, int, GAME*);
typedef void (*aINS_position_move_proc)(ACTOR*);
typedef ACTOR* (*aINS_search_near_insect_proc)(GAME*, f32, f32);

/* sizeof(aINS_Clip_c) == 0x50 */
typedef struct ac_insect_clip_s {
  /* 0x00 */ aINS_make_insect_proc make_insect_proc;
  /* 0x04 */ aINS_make_ant_proc make_ant_proc; // unused clip proc in AC
  /* 0x08 */ void* unused_08;
  /* 0x0C */ aINS_dt_proc dt_proc;
  /* 0x10 */ aINS_make_actor_proc make_actor_proc;
  /* 0x14 */ aINS_set_pl_act_tim_proc set_pl_act_tim_proc;
  /* 0x18 */ aINS_chk_live_insect_proc chk_live_insect_proc;
  /* 0x1C */ aINS_search_near_insect_proc search_near_insect_proc;
  /* 0x20 */ int pl_action;
  /* 0x24 */ int pl_action_ut_x;
  /* 0x28 */ int pl_action_ut_z;
  /* 0x2C */ aINS_position_move_proc position_move_proc;
  /* 0x30 */ int ant_spawn_pending;
  /* 0x34 */ aINS_Init_c ant_spawn_info;
  /* 0x4C */ u8 ant_ut_x;
  /* 0x4D */ u8 ant_ut_z;
} aINS_Clip_c;

#ifdef __cplusplus
}
#endif

#endif
