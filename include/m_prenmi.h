#ifndef M_PRENMI_H
#define M_PRENMI_H

#include "types.h"
#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PRENMI_TIMER 30

/* sizeof(struct game_prenmi_s) == 0xE8 */
typedef struct game_prenmi_s {
  GAME game;
  int timer;
  u32 unused_pad;
} GAME_PRENMI;

extern void prenmi_init(GAME* game);
extern void prenmi_cleanup(GAME* game);

#ifdef __cplusplus
};
#endif

#endif
