#ifndef AC_GYO_RELEASE_H
#define AC_GYO_RELEASE_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct gyo_release_actor_s GYO_RELEASE_ACTOR;

/* sizeof(GYO_RELEASE_ACTOR) == 0x1BC */
struct gyo_release_actor_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ ACTOR* gyoei_actor_p;
    /* 0x178 */ int gyo_type;
    /* 0x17C */ s16 size_type;
    /* 0x180 */ int anime_frame;
    /* 0x184 */ int segment;
    /* 0x188 */ int _188;
    /* 0x18C */ ClObjPipe_c col_pipe;
    /* 0x1A8 */ s16 angle_xz;
    /* 0x1AA */ s16 angle_y;
    /* 0x1AC */ s16 angle_y_add;
    /* 0x1AE */ s16 exist_timer;
    /* 0x1B0 */ f32 shadow_scale;
    /* 0x1B4 */ u8 exist_flag;
    /* 0x1B5 */ u8 _1B5;
    /* 0x1B6 */ s16 revert_position_flag;
    /* 0x1B8 */ int revert_position_timer;
};

extern ACTOR_PROFILE Gyo_Release_Profile;

#ifdef __cplusplus
}
#endif

#endif
