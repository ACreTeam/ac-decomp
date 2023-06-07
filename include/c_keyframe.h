#ifndef C_KEYFRAME_H
#define C_KEYFRAME_H

#include "types.h"
#include "PR/mbi.h"
#include "game.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct joint_s {
  Gfx* model;
  u8 child;
  u8 flags;
  s_xyz translation;
} cKF_Joint_R_c;

typedef struct skeleton_s {
  u8 num_joints;
  u8 num_shown_joints;
  cKF_Joint_R_c* joint_table;
} cKF_Skeleton_R_c;

typedef struct animation_s {
  u8* flag_table;
  s16* data_table;
  s16* key_table;
  s16* fixed_table;
  s16 pad;
  s16 frames;
} cKF_Animation_R_c;

enum {
  cKF_FRAMECONTROL_STOP,
  cKF_FRAMECONTROL_REPEAT,

  cKF_FRAMECONTROL_NUM
};

typedef struct frame_control_s {
  f32 start_frame;
  f32 end_frame;
  f32 max_frames;
  f32 speed;
  f32 current_frame;
  int mode;
} cKF_FrameControl_c;

typedef struct skeleton_info_s {
  cKF_FrameControl_c frame_control;
  cKF_Skeleton_R_c* skeleton;
  cKF_Animation_R_c* animation;

  f32 morph_counter;
  s_xyz* current_joint;
  s_xyz* target_joint;
  s_xyz* rotation_diff_table;

  int animation_enabled;
  xyz_t base_world_position;
  s16 base_angle_y;

  xyz_t base_model_translation;
  s_xyz base_model_rotation;
  s_xyz updated_base_model_rotation;

  f32 fixed_counter;
  xyz_t model_world_position_correction;
  s16 model_angle_correction;
} cKF_SkeletonInfo_R_c;

typedef struct combine_work_set_s {
    cKF_SkeletonInfo_R_c* keyframe;
    u8* anm_check_bit_tbl;
    s16* anm_const_val_tbl;
    s16* anm_data_src;
    s16* anm_key_num;
    int anm_key_num_idx;
    int anm_const_val_tbl_idx;
    int anm_data_src_idx;
}cKF_SkeletonInfo_R_combine_work_c;

typedef int (*cKF_draw_callback)(GAME*, cKF_SkeletonInfo_R_c*, int, Gfx**, u8*, void*, s_xyz*, xyz_t*);


#define cKF_FRAMERATE 30.0f
#define cKF_FRAMETIME (1.0f / cKF_FRAMERATE)
#define cKF_EPSILON 0.008f

extern f32 cKF_HermitCalc(f32 t, f32 tension, f32 p0, f32 p1, f32 m0, f32 m1);
extern void cKF_SkeletonInfo_subRotInterpolation(f32 t, s16* out, s16 rot1, s16 rot2);

extern void cKF_SkeletonInfo_R_ct(cKF_SkeletonInfo_R_c* keyframe, cKF_Skeleton_R_c* skeleton, cKF_Animation_R_c* animation, s_xyz* work_table, s_xyz* target_table);
extern void cKF_SkeletonInfo_R_dt();

extern void cKF_SkeletonInfo_R_init_standard_stop(cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation, s_xyz* rotation_diff_table);
extern void cKF_SkeletonInfo_R_init_standard_stop_morph(cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation, s_xyz* rotation_diff_table, f32 morph);
extern void cKF_SkeletonInfo_R_init_standard_repeat(cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation, s_xyz* rotation_diff_table);
extern void cKF_SkeletonInfo_R_init_standard_repeat_morph(cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation, s_xyz* rotation_diff_table, f32 morph);

extern void cKF_SkeletonInfo_R_init(cKF_SkeletonInfo_R_c* keyframe, cKF_Skeleton_R_c* skeleton, cKF_Animation_R_c* animation, f32 start_frame, f32 end_frame, 
f32 current_frame, f32 frame_speed, f32 morph_counter,int mode,s_xyz* rotation_diff_table);

extern int cKF_Animation_R_play(cKF_SkeletonInfo_R_c* keyframe);

extern void cKF_Si3_draw_SV_R_child(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int* joint_num, cKF_draw_callback prerender_callback, cKF_draw_callback postrender_callback, void* arg, Mtx** mtxpp);
extern void cKF_Si3_draw_R_SV(GAME* game, cKF_SkeletonInfo_R_c* keyframe, Mtx* mtxp, cKF_draw_callback prerender_callback, cKF_draw_callback postrender_callback, void* arg);

extern void cKF_SkeletonInfo_R_init_standard_repeat_speedsetandmorph(cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation, s_xyz* rotation_diff_table, f32 frame_speed, f32 morph_counter);
extern void cKF_SkeletonInfo_R_init_standard_repeat_setframeandspeedandmorph(cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation, s_xyz* rotation_diff_table, f32 frame, f32 frame_speed, f32 morph_counter);
extern void cKF_SkeletonInfo_R_init_standard_setframeandspeedandmorphandmode(cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation, s_xyz* rotation_diff_table, f32 frame, f32 frame_speed, f32 morph_counter, int mode);
extern void cKF_SkeletonInfo_R_init_reverse_setspeedandmorphandmode(cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation, s_xyz* rotation_diff_table, f32 frame_speed, f32 morph_counter, int mode);

extern void cKF_SkeletonInfo_R_combine_work_set(cKF_SkeletonInfo_R_combine_work_c* combine, cKF_SkeletonInfo_R_c* keyframe);
extern void cKF_SkeletonInfo_R_combine_translation(s16** joint, int* flag, cKF_SkeletonInfo_R_combine_work_c* combine , s8* cwork_num);
extern void cKF_SkeletonInfo_R_combine_rotation(s16** joint, int* flag, cKF_SkeletonInfo_R_combine_work_c* combine , s8* cwork_num);

extern int cKF_SkeletonInfo_R_combine_play(cKF_SkeletonInfo_R_c* info1, cKF_SkeletonInfo_R_c* info2,s8* flag);

extern void cKF_SkeletonInfo_R_T_combine_play(int* arg1, int* arg2, int* arg3,cKF_SkeletonInfo_R_c* info1, cKF_SkeletonInfo_R_c* info2, cKF_SkeletonInfo_R_c* info3,s8* flag);
extern void cKF_SkeletonInfo_R_Animation_Set_base_shape_trs(f32 transx, f32 transy, f32 transz, cKF_SkeletonInfo_R_c* keyframe, s16 anglex, s16 angley, s16 anglez);
extern void cKF_SkeletonInfo_R_AnimationMove_ct_base(f32 counter, xyz_t* basepos, xyz_t* correctpos, s16 ybase, s16 yidle, cKF_SkeletonInfo_R_c* keyframe, int animation_flag);
extern void cKF_SkeletonInfo_R_AnimationMove_dt(cKF_SkeletonInfo_R_c* keyframe);
extern void cKF_SkeletonInfo_R_AnimationMove_base(xyz_t* base, s_xyz* sbase, xyz_t* move, s16 yidle, cKF_SkeletonInfo_R_c* keyframe);

extern void cKF_SkeletonInfo_R_AnimationMove_CulcTransToWorld(f32 calcx, f32 calcy, f32 calcz, xyz_t* base, xyz_t* calcp, s16 val, xyz_t* trans, cKF_SkeletonInfo_R_c* keyframe, int animation_flag);

#ifdef __cplusplus
}
#endif

#endif