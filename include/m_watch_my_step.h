#ifndef M_WATCH_MY_STEP_H
#define M_WATCH_MY_STEP_H

#include "types.h"
#include "m_play.h"
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

extern Gfx fki_win_mode[];
extern Gfx fki_win_w3T_model[];
extern Gfx fki_win_w2T_model[];
extern Gfx fki_win_w4_model[];
extern Gfx fki_win_w1T_model[];

extern Gfx cam_win_winT_model[];
extern Gfx cam_win_cT_model[];
extern Gfx cam_win_mojiT_model[];
extern Gfx cam_win_yajirushi_model[];

extern Gfx elc_win_winT_model[];
extern Gfx elc_win_zT_model[];
extern Gfx elc_win_moji_model[];
extern Gfx elc_win_moji2T_model[];

extern Gfx mny_win_ueT_model[];
extern Gfx mny_win_beruT_model[];
extern Gfx mny_win_mojiT_model[];

extern void watch_my_step_ct();
extern void watch_my_step_move(GAME_PLAY* play);
extern void watch_my_step_draw(GAME_PLAY* play);

extern void navigate_camera_ct();
extern void navigate_camera_move(GAME_PLAY* play);
extern void navigate_camera_draw(GAME_PLAY* play);

extern void mWt_mybell_confirmation_ct();
extern void mWt_mybell_confirmation_move(GAME_PLAY* play);
extern void mWt_mybell_confirmation_draw(GAME_PLAY* play);

#ifdef __cplusplus
}
#endif

#endif
