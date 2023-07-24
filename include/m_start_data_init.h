#ifndef M_START_DATA_INIT_H
#define M_START_DATA_INIT_H

#include "types.h"
#include "game_h.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  mSDI_INIT_MODE_NEW,
  mSDI_INIT_MODE_NEW_PLAYER,
  mSDI_INIT_MODE_FROM,
  mSDI_INIT_MODE_PAK,
  mSDI_INIT_MODE_ERR,

  mSDI_INIT_MODE_NUM
};

enum {
  mSDI_MALLOC_FLAG_GAME,
  mSDI_MALLOC_FLAG_ZELDA,

  mSDI_MALLOC_FLAG_NUM
};

extern void mSDI_StartInitAfter(GAME* game, int renewal_reserve_flag, int malloc_flag);
extern int mSDI_StartInitBefore(GAME* game, int player_no, int init_mode, int malloc_flag);
extern int mSDI_StartDataInit(GAME* game, int player_no, int init_mode);

#ifdef __cplusplus
}
#endif

#endif
