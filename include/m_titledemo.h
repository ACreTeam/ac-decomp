#ifndef M_TITLEDEMO_H
#define M_TITLEDEMO_H

#include "types.h"
#include "m_play_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mTD_TITLE_DEMO_NUM 5

/* key presses for title screen */
extern u16 pact0_key_data[];
extern u16 pact1_key_data[];
extern u16 pact2_key_data[];
extern u16 pact3_key_data[];
extern u16 pact4_key_data[];

/* initial state for title screen */
extern u16 pact0_head_table[];
extern u16 pact1_head_table[];
extern u16 pact2_head_table[];
extern u16 pact3_head_table[];
extern u16 pact4_head_table[];

extern int mTD_demono_get();
extern void title_demo_move(GAME_PLAY* play);
extern void mTD_player_keydata_init(GAME_PLAY* play);
extern void mTD_rtc_set();
extern void mTD_rtc_reserve();
extern int mTD_get_titledemo_no();
extern int mTD_tdemo_button_ok_check();

#ifdef __cplusplus
}
#endif

#endif
