#ifndef M_FUUSEN_H
#define M_FUUSEN_H

#include "types.h"
#include "m_play_h.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  Balloon_STATE_DEAD, /* Doesn't exist */
  Balloon_STATE_CHK_SPAWN, /* Check should spawn */
  Balloon_STATE_SPAWNED, /* Sucessfully spawned */
  Balloon_STATE_LOOK_UP, /* Flew away after hitting a tree? */
  Balloon_STATE_PENDING_SPAWN, /* Didn't successfully spawn, trying again */

  Balloon_STATE_NUM
};

extern int fuusen_DEBUG_mode_flag;

extern void Balloon_init(GAME_PLAY*);
extern void Balloon_make_fuusen(GAME_PLAY* play);
extern void Balloon_chk_make_fuusen(GAME_PLAY* play);
extern void Balloon_move(GAME_PLAY* play);
extern void Balloon_kill();
extern void Balloon_look_up();

#ifdef __cplusplus
}
#endif

#endif
