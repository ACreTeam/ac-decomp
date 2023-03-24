#ifndef FIRST_GAME_H
#define FIRST_GAME_H

#include "types.h"
#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(struct game_first_s) == 0xE0 */
typedef struct game_first_s {
  /* 0x00 */ GAME game;
} GAME_FIRST;

extern void first_game_cleanup(GAME_FIRST* first_game);
extern void first_game_init(GAME_FIRST* first_game);

#ifdef __cplusplus
}
#endif

#endif
