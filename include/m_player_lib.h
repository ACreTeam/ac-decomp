#ifndef M_PLAYER_LIB_H
#define M_PLAYER_LIB_H

#include "types.h"
#include "m_player.h"
#include "m_private_h.h"

#ifdef __cplusplus
extern "C" {
#endif

extern PLAYER_ACTOR* get_player_actor_withoutCheck(GAME_PLAY* play);
extern void mPlib_SetData1_controller_data_for_title_demo(f32 stick_x, f32 stick_y, int btn_a, int btn_b);
extern void mPlib_SetData2_controller_data_for_title_demo(mActor_name_t tool);
extern void mPlib_request_main_invade_type1(GAME_PLAY* play);
extern mActor_name_t mPlib_Get_itemNo_forWindow();
extern int mPlib_check_able_change_camera_normal_index();
extern void mPlib_request_main_refuse_type1(GAME_PLAY* play);
extern void mPlib_request_main_wait_type3(GAME_PLAY* play);
extern void mPlib_Set_able_force_speak_label(ACTOR* actor);
extern int mPlib_request_main_demo_walk_type1(GAME* game, f32 goal_x, f32 goal_z, f32 speed, int flag);
extern void mPlib_Set_goal_player_demo_walk(f32 goal_x, f32 goal_z, f32 speed);
extern void mPlib_Set_able_hand_all_item_in_demo(s8 enable);
extern void mPlib_change_player_cloth_info_lv2(Private_c* priv, mActor_name_t cloth_name);
extern int mPlib_Get_address_able_display();
extern int mPlib_get_player_actor_main_index(GAME_PLAY* play);

#ifdef __cplusplus
}
#endif

#endif
