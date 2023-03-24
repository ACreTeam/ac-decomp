#ifndef M_TRADEMARK_H
#define M_TRADEMARK_H

#include "types.h"
#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(struct game_trademark_s) == 0x25A70 */
typedef struct game_trademark_s {
  /* 0x000000 */ GAME game;
  // TODO: finish
  /* 0x0000E0 */ u8 _temp[0x25990];
} GAME_TRADEMARK;

extern void trademark_init(GAME_TRADEMARK* trademark);
extern void trademark_cleanup(GAME_TRADEMARK* trademark);

#ifdef __cplusplus
}
#endif

#endif
