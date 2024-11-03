#ifndef AC_SET_OVL_GYOEI_H
#define AC_SET_OVL_GYOEI_H

#include "types.h"
#include "ac_set_manager.h"
#include "ac_gyoei.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aSOG_TERM_TRANSITION_MAX_DAYS 5

enum fish_spawn_area {
  aSOG_SPAWN_AREA_POOL, /* river pool */
  aSOG_SPAWN_AREA_WATERFALL,
  aSOG_SPAWN_AREA_RIVER_MOUTH,
  aSOG_SPAWN_AREA_OFFING, /* aka 'deep sea' */
  aSOG_SPAWN_AREA_SEA,
  aSOG_SPAWN_AREA_RIVER,
  aSOG_SPAWN_AREA_POND,

  aSOG_SPAWN_AREA_NUM
};

#define aSOG_TIME_NO_0_END 3      /* 9pm-3:59am */
#define aSOG_TIME_NO_1_END 8      /* 4am-8:59am */
#define aSOG_TIME_NO_2_END 12 + 3 /* 9am-3:59pm */
#define aSOG_TIME_NO_3_END 12 + 8 /* 4pm-8:59pm */

/* number of terms in a given month */
enum fish_term {
  aSOG_TERM_0,
  aSOG_TERM_1,

  aSOG_TERM_NUM
};

enum time_no {
  aSOG_TIME_0,
  aSOG_TIME_1,
  aSOG_TIME_2,
  aSOG_TIME_3,

  aSOG_TIME_NUM
};

enum range_proc {
  aSOG_RANGE_PROC_RIVER,
  aSOG_RANGE_PROC_SEA,
  aSOG_RANGE_PROC_OFFING,
  aSOG_RANGE_PROC_POOL,
  aSOG_RANGE_PROC_FISHING_EVENT,
  aSOG_RANGE_PROC_ISLAND,

  aSOG_RANGE_PROC_NUM
};

extern int aSOG_gyoei_set(SET_MANAGER* set_manager, GAME_PLAY* play);

#ifdef __cplusplus
}
#endif

#endif
