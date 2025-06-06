#ifndef AC_GYOEI_H_H
#define AC_GYOEI_H_H

#include "types.h"
#include "game.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    aGYO_BALLCHECK_TYPE_NORMAL,
    aGYO_BALLCHECK_TYPE_SNOWMAN,

    aGYO_BALLCHECK_TYPE_NUM
};

/* sizeof(aGYO_Init_c) == 0x18 */
typedef struct gyoei_init_s {
  /* 0x00 */ int fish_type;
  /* 0x04 */ xyz_t position;
  /* 0x10 */ int extra_data;
  /* 0x14 */ GAME* game;
} aGYO_Init_c;

typedef int (*aGYO_make_proc)(aGYO_Init_c*);
typedef void (*aGYO_dt_proc)(ACTOR*, GAME*);
typedef void (*aGYO_ballcheck_proc)(xyz_t*, f32, s16);
typedef void (*aGYO_hitcheck_proc)(xyz_t*, s16);
typedef int (*aGYO_chk_live_proc)(int, int, GAME*);
typedef ACTOR* (*aGYO_search_near_proc)(f32, f32);

/* sizeof(aGYO_Clip_c) == 0x1C */
typedef struct ac_gyoei_clip_s {
  /* 0x00 */ aGYO_make_proc make_gyoei_proc;
  /* 0x04 */ int unused_04; // unused clip proc in AC
  /* 0x08 */ aGYO_dt_proc dt_gyoei_proc;
  /* 0x0C */ aGYO_ballcheck_proc ballcheck_gyoei_proc;
  /* 0x10 */ aGYO_hitcheck_proc hitcheck_gyoei_proc;
  /* 0x14 */ aGYO_chk_live_proc chk_live_gyoei_proc;
  /* 0x18 */ aGYO_search_near_proc search_near_gyoei_proc;
} aGYO_Clip_c;

#ifdef __cplusplus
}
#endif

#endif
