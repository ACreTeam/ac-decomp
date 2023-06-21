#ifndef M_PLAY_H
#define M_PLAY_H

#include "types.h"
#include "game.h"
#include "libultra/ultratypes.h"
#include "m_view.h"
#include "m_camera2.h"
#include "m_submenu.h"
#include "m_pause.h"
#include "m_field_info.h"
#include "m_fbdemo_wipe.h"
#include "m_play_h.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(struct game_play_s) == 0x2600 */
struct game_play_s {
  /* 0x0000 */ GAME game;
  // TODO: finish
  /* 0x00E0 */ int _00E0;
  /* 0x00E4 */ mFI_block_tbl_c block_table;
  /* 0x00F4 */ mFI_block_tbl_c last_block_table;
  /* 0x0104 */ u8 _0104[0x1A68 - 0x0104];
  /* 0x1A68 */ View view;
  /* 0x1B88 */ Camera2 camera;
  /* 0x1CC0 */ u8 _1CC0[0x1DA0 - 0x1CC0];
  /* 0x1DA0 */ pause_t pause;
  /* 0x1DA8 */ Actor_info actor_info;
  /* 0x1DEC */ Submenu submenu;
  /* 0x1FA4 */ u8 _1FA4[0x2008 - 0x1FA4];
  /* 0x2008 */ int next_scene_no;
  /* 0x200C */ MtxF matrix;
  /* 0x204C */ u8 _204C[0x20D0-0x204C];
  /* 0x20D0 */ u8 fb_fade_type;
  /* 0x20D1 */ u8 fb_wipe_type;
  /* 0x20D2 */ u8 fb_mode;
  /* 0x20D3 */ u8 fb_wipe_mode;
  /* 0x20D4 */ //int _20D4;
  /* 0x20D8 */ fbdemo_wipe fbdemo_wipe;
  /* 0x2318 */ fbdemo_fade color_fade;
  /* 0x2328 */ u8 _2328[0x2600 - 0x2328];
};


extern void play_init(GAME_PLAY* play);
extern void play_cleanup(GAME_PLAY* play);

#ifdef __cplusplus
}
#endif

#endif
