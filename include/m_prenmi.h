#ifndef M_PRENMI_H
#define M_PRENMI_H

#include "types.h"
#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(struct game_prenmi_s) == 0xE8 */
typedef struct game_prenmi_s {
  GAME game;
  u32 timer;
  u32 pad;
} GAME_PRENMI;

extern void prenmi_init(GAME_PRENMI* prenmi);
extern void prenmi_cleanup(GAME_PRENMI* prenmi);

#ifdef __cplusplus
};
#endif

#endif
