#ifndef M_PLAYER_LIB_H
#define M_PLAYER_LIB_H

#include "types.h"
#include "m_player.h"

#ifdef __cplusplus
extern "C" {
#endif

extern PLAYER_ACTOR* get_player_actor_withoutCheck(GAME_PLAY* play);
extern void mPlib_SetData1_controller_data_for_title_demo(f32 stick_x, f32 stick_y, int btn_a, int btn_b);
extern void mPlib_SetData2_controller_data_for_title_demo(mActor_name_t tool);
extern void mPlib_request_main_invade_type1(GAME_PLAY* play);

#ifdef __cplusplus
}
#endif

#endif
