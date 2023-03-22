#ifndef GAME_H
#define GAME_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct game_s {
  /* 0x009E */ u8 disable_display;
  /* 0x00A4 */ u8 disable_prenmi;
} GAME;

extern void game_ct(GAME* game);
extern void game_dt(GAME* game);
extern void game_main(GAME* game);
extern u8 game_is_doing(GAME*);

extern GAME* game_class_p;

#ifdef __cplusplus
};
#endif

#endif
