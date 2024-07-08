#ifndef AC_T_KEITAI_H
#define AC_T_KEITAI_H

#include "types.h"
#include "ac_tools.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Keitai_Profile;

typedef void (*KEITAI_PROC)(ACTOR*);

typedef struct t_keitai_s {
    TOOLS_ACTOR tools_class;
    KEITAI_PROC action_proc;
    int action;
    cKF_SkeletonInfo_R_c keyframe;
    s_xyz work[4];
    s_xyz morph[4];
    char* bank_ram_start;
} KEITAI_ACTOR;

typedef struct t_keitai_action_anim_s {
    cKF_Animation_R_c* animation;
    f32 start_frame;
    f32 end_frame;
} KEITAI_ACTION_ANIM;

#ifdef __cplusplus
}
#endif

#endif
