#ifndef M_HUUSUI_ROOM_H
#define M_HUUSUI_ROOM_H

#include "types.h"
#include "game.h"
#include "m_private.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Feng Shui related functions
 * 
 * Brief overview of how Feng Shui works:
 *   Money Power: increased money "luck"
 *   Goods power: increased item "luck"
 * 
 *   Feng Shui Colors:
 *     - NONE: no bonus
 *     - YELLOW: money power bonus on west side (+4)
 *     - RED: goods power bonus on east side (+4)
 *     - ORANGE: money & goods power bonuses on north side (+2 each)
 *     - GREEN: money & goods power bonuses on south side (+2 each)
 *     - LUCKY: money & goods power anywhere in house (+4 each)
 * 
 * Feng Shui directional bonuses will only apply if all units
 * of the furniture are in the same directional category. For
 * example, if a green table (2x2) only has two units of its
 * four unit total in the south direction, you will NOT get
 * a bonus. Additionally, the smallest level house only has
 * one unit columns/rows for Feng Shui while all other rooms
 * have two columns/rows. This means that you can never get
 * a Feng Shui bonus from 2x2 furniture in the smallest house.
 * 
 * There is also a 'doll'/'face' deduction. If you rotate furniture
 * marked as a doll/has_face towards the wall which is is adjacent to,
 * you will get a -5 point luck penalty. This happens even when the
 * Feng Shui type of the furniture is 'NONE'.
 **/

#define mHsRm_GOODS_POWER_MAX 40

/* Feng Shui colors */
enum {
  mHsRm_HUUSUI_NONE,
  mHsRm_HUUSUI_YELLOW,
  mHsRm_HUUSUI_RED,
  mHsRm_HUUSUI_ORANGE,
  mHsRm_HUUSUI_GREEN,
  mHsRm_HUUSUI_LUCKY,

  mHsRm_HUUSUI_NUM
};

/* Feng Shui house room directions */
enum {
  mHsRm_DIRECTION_SOUTH,
  mHsRm_DIRECTION_EAST,
  mHsRm_DIRECTION_NORTH,
  mHsRm_DIRECTION_WEST,

  mHsRm_DIRECTION_NUM
};

extern void mHsRm_GetHuusuiRoom(GAME* game, int player_no);

#ifdef __cplusplus
}
#endif

#endif
