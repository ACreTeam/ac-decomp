#ifndef M_PLAY_H
#define M_PLAY_H

#include "types.h"
#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(struct game_play_s) == 0x2600 */
typedef struct game_play_s {
  /* 0x0000 */ GAME game;
  // TODO: finish
  /* 0x00E0 */ u8 _temp[0x2520];
} GAME_PLAY;

extern void play_init(GAME_PLAY* play);
extern void play_cleanup(GAME_PLAY* play);

#ifdef __cplusplus
}
#endif

#endif
