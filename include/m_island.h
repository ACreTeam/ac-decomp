#ifndef M_ISLAND_H
#define M_ISLAND_H

#include "types.h"
#include "m_personal_id.h"
#include "m_npc.h"
#include "m_land.h"
#include "m_field_make.h"
#include "m_home.h"
#include "m_needlework.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mISL_ISLANDER_NUM 1

#define mISL_ISLAND_NAME_LEN 8

#define mISL_FG_BLOCK_X_NUM 2
#define mISL_FG_BLOCK_Z_NUM 1

#define mISL_BLOCK_X0 4
#define mISL_BLOCK_X1 5
#define mISL_BLOCK_Z 8

enum {
  mISL_ISLAND_BLOCK_LEFT,
  mISL_ISLAND_BLOCK_RIGHT,

  mISL_ISLAND_BLOCK_NUM
};

/* sizeof(Island_c) == 0x1900 */
typedef struct island_s {
  /* 0x0000 */ u8 name[mISL_ISLAND_NAME_LEN]; /* island name */
  /* 0x0008 */ mLd_land_info_c landinfo; /* land info for town */
  /* 0x0014 */ mFM_fg_c fgblock[mISL_FG_BLOCK_Z_NUM][mISL_FG_BLOCK_X_NUM]; /* island item actor data */
  /* 0x0418 */ mHm_cottage_c cottage; /* player shared cottage data */
  /* 0x0CE0 */ mNW_original_design_c flag_design; /* island flag design */
  /* 0x0F00 */ Animal_c animal; /* islander info */
  /* 0x1888 */ u16 deposit[mISL_FG_BLOCK_X_NUM * mISL_FG_BLOCK_Z_NUM][UT_Z_NUM]; /* buried item bitfield */
  /* 0x18C8 */ u8 bg_data[mISL_ISLAND_BLOCK_NUM]; /* island acre ids */
  /* 0x18CA */ lbRTC_time_c renew_time; /* last time island was visited? */
  /* 0x18D2 */ u8 unused_18D2[14]; /* unused */
  /* 0x18E0 */ u8 grass_tex_type; /* grass type */
  /* 0x18E1 */ u8 last_song_male; /* last song kapp'n sang for a male character */
  /* 0x18E2 */ u8 last_song_female; /* last song kapp'n sang for a female character */
  /* 0x18E3 */ u8 unused_18E3[29]; /* unused */
} Island_c;

extern void mISL_ClearKeepIsland();
extern void mISL_init(Island_c* island);

#ifdef __cplusplus
}
#endif

#endif
