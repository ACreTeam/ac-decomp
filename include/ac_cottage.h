#ifndef AC_COTTAGE_H
#define AC_COTTAGE_H

#include "types.h"
#include "m_common_data.h"
#include "ac_structure.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*COTTAGE_REWRITE_DOOR_PROC)(ACTOR*, GAME_PLAY*);
typedef void (*COTTAGE_SET_BG_OFFSET_PROC)(STRUCTURE_ACTOR*, int);
typedef int (*COTTAGE_CHECK_DOOR_IN_PROC)(STRUCTURE_ACTOR*, GAME_PLAY*);
typedef int (*COTTAGE_CHECK_DOOR_OUT_PROC)(STRUCTURE_ACTOR*, GAME_PLAY*);
typedef void (*COTTAGE_DEMO_DOOR_OPEN_PROC)(ACTOR*);
typedef f32 (*COTTAGE_LIGHT_AIM_PROC)(STRUCTURE_ACTOR*);
typedef void (*COTTAGE_LIGHT_CONTROL_PROC)(STRUCTURE_ACTOR*);

typedef struct t_cottage_data_s {
    cKF_Skeleton_R_c* skl;
    cKF_Animation_R_c* in_anim;
    cKF_Animation_R_c* out_anim;
    s16 structure_type;
    s16 structure_palette;
    Gfx* model;
    bIT_ShadowData_c* shadow_data;
    mActor_name_t actor_name;
    Door_data_c* door_data;
    COTTAGE_REWRITE_DOOR_PROC rewrite_door_proc; // Checked?
    COTTAGE_SET_BG_OFFSET_PROC set_bg_offset_proc; // Checked
    COTTAGE_CHECK_DOOR_IN_PROC check_door_in_proc; // Maybe actor?
    COTTAGE_CHECK_DOOR_OUT_PROC check_door_out_proc; // Maybe actor?
    COTTAGE_DEMO_DOOR_OPEN_PROC demo_door_open_proc; // Checked
    COTTAGE_LIGHT_AIM_PROC light_aim_proc; // Checked?
    COTTAGE_LIGHT_CONTROL_PROC light_control_proc; // Checked
} COTTAGE_DATA;

extern ACTOR_PROFILE Cottage_My_Profile;
extern ACTOR_PROFILE Cottage_Npc_Profile;

#ifdef __cplusplus
}
#endif

#endif

