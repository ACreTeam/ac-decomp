#ifndef AC_SNOWMAN_H
#define AC_SNOWMAN_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aSMAN_SCALE_MAX (6400.0f)

typedef void (*aSMAN_PROC)(ACTOR* actorx, GAME* game);

typedef struct snowman_actor_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ ClObjPipe_c col_pipe;
    /* 0x190 */ aSMAN_PROC process;
    /* 0x194 */ ACTOR* col_actor;
    /* 0x198 */ xyz_t _198;
    /* 0x1A4 */ xyz_t rev_pos;
    /* 0x1B0 */ xyz_t fg_pos;
    /* 0x1BC */ f32 y_ofs;
    /* 0x1C0 */ f32 _1C0;
    /* 0x1C4 */ f32 base_speed;
    /* 0x1C8 */ f32 accel;
    /* 0x1CC */ f32 roll_speed;
    /* 0x1D0 */ f32 normalized_scale; /* normalized ball scale, [0, 1.0f] */
    /* 0x1D4 */ f32 body_scale;
    /* 0x1D8 */ f32 move_dist; /* [0, 6400.0f] */
    /* 0x1DC */ f32 _1DC;
    /* 0x1E0 */ int result;
    /* 0x1E4 */ int msg_no;
    /* 0x1E8 */ int snowman_part;
    /* 0x1EC */ s_xyz head_vec;
    /* 0x1F2 */ s_xyz ground_angle;
    /* 0x1F8 */ s16 flags;
    /* 0x1FA */ s16 timer;
} SNOWMAN_ACTOR;

extern ACTOR_PROFILE Snowman_Profile;

#ifdef __cplusplus
}
#endif

#endif
