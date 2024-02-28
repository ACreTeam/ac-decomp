#ifndef AC_MBG_H
#define AC_MBG_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mbg_actor_s MBG_ACTOR;

struct mbg_actor_s {
    ACTOR actor;
    mCoBG_bg_regist_c move_bg_regist;
    int move_bg_regist_idx;
    xyz_t original_pos;
    f32 move_counter;
};

extern ACTOR_PROFILE Mbg_Profile;

#ifdef __cplusplus
}
#endif

#endif
