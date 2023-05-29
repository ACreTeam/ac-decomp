#ifndef SECOND_GAME_H
#define SECOND_GAME_H

#include "types.h"
#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(struct second_game_s) == 0xE0 */
typedef struct second_game_s {
  /* 0x00 */ GAME game;
} GAME_SECOND;

extern void second_game_init(GAME* game);
extern void second_game_cleanup(GAME* game);

#ifdef __cplusplus
}
#endif

#endif
