#ifndef M_ROLL_LIB_H
#define M_ROLL_LIB_H

#include "types.h"
#include "m_lib.h"
#include "m_actor.h"
#include "m_play_h.h"
#include "m_demo.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mRlib_spdXZ_to_spdF_Angle(xyz_t* speed_vec, f32* speedf, s16* angle_y_s);
extern void mRlib_spdF_Angle_to_spdXZ(xyz_t* speed_vec, f32* speedf, s16* angle_y_s);
extern int mRlib_position_move_for_sloop(ACTOR* actor, s_xyz* slope_angle);
extern int mRlib_Get_norm_Clif(ACTOR* actor, xyz_t* normal_vec);
extern void mRlib_Roll_Matrix_to_s_xyz(ACTOR* actor, s_xyz* rot, s16 angle);
extern s16 mRlib_Get_HitWallAngleY(ACTOR* actor);
extern void mRlib_Station_step_modify_to_wall(ACTOR* actor);
extern int mRlib_Set_Position_Check(ACTOR* actor);
extern int mRlib_HeightGapCheck_And_ReversePos(ACTOR* actor);
extern int mRlib_Hole_check(ACTOR* actor);
extern int mRlib_Get_ground_norm_inHole(ACTOR* actor, xyz_t* normal, f32* dist, s16* angle_y, s16* angle_rate, f32 rate_mod);
extern int mRlib_PSnowmanBreakCheck(ACTOR* actor, GAME_PLAY* play, f32* speed);
extern int mRlib_PSnowmanBreakNeckSwing(s16* head_angle_y, f32 f0, f32 scale);
extern int mRlib_PSnowman_NormalTalk(ACTOR* actor, GAME_PLAY* play, f32* speed, mDemo_REQUEST_PROC demo_req_proc);
extern int mRlib_snowman_ball_unit_check_from_pos(GAME_PLAY* play, const xyz_t* wpos);

#ifdef __cplusplus
}
#endif

#endif
