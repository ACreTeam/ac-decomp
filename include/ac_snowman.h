#ifndef AC_SNOWMAN_H
#define AC_SNOWMAN_H

#include "types.h"
#include "m_actor.h"
#include "m_snowman.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aSMAN_MOVE_DIST_MAX (6400.0f)

#define aSMAN_FLAG_HEAD_JUMP (1 << 0)
#define aSMAN_FLAG_ON_GROUND (1 << 1)
#define aSMAN_FLAG_MOVED (1 << 2)
#define aSMAN_FLAG_IN_HOLE (1 << 3)
#define aSMAN_FLAG_4 (1 << 4) // unused?
#define aSMAN_FLAG_COMBINED (1 << 5)
#define aSMAN_FLAG_NO_SPEAK (1 << 6)
#define aSMAN_FLAG_DELETE (1 << 7)

typedef int (*aSMAN_PROC)(ACTOR* actorx, GAME* game);

typedef struct snowman_actor_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ ClObjPipe_c col_pipe;
    /* 0x190 */ aSMAN_PROC process;
    /* 0x194 */ ACTOR* col_actor;
    /* 0x198 */ xyz_t combine_dist;
    /* 0x1A4 */ xyz_t rev_pos;
    /* 0x1B0 */ xyz_t fg_pos;
    /* 0x1BC */ f32 y_ofs;
    /* 0x1C0 */ f32 fall_height;
    /* 0x1C4 */ f32 base_speed;
    /* 0x1C8 */ f32 accel;
    /* 0x1CC */ f32 roll_speed;
    /* 0x1D0 */ f32 normalized_scale; /* normalized ball scale, [0, 1.0f] */
    /* 0x1D4 */ f32 body_scale;
    /* 0x1D8 */ f32 move_dist; /* [0, 6400.0f] */
    /* 0x1DC */ f32 impact_speed;
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
