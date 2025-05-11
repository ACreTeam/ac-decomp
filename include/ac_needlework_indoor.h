#ifndef AC_NEEDLEWORK_INDOOR_H
#define AC_NEEDLEWORK_INDOOR_H

#include "types.h"
#include "m_actor.h"
#include "m_needlework.h"
#include "ac_needlework_indoor_clip.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct needlework_indoor_movebg_s {
    xyz_t pos;
    mCoBG_bg_regist_c regist;
    int regist_idx;
} aNI_MoveBg_c;

typedef struct needlework_indoor_actor_s NEEDLEWORK_INDOOR_ACTOR;

/* sizeof(NEEDLEWORK_INDOOR_ACTOR) == 0x3F0 */
struct needlework_indoor_actor_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ u8 _174[0x188 - 0x174];
    /* 0x188 */ mNW_original_design_c* data[2][mNW_TYPE_NUM][mNW_DESIGN_NUM];
    /* 0x1C8 */ int design_buf_idx[mNW_TYPE_NUM][mNW_DESIGN_NUM];
    /* 0x1E8 */ aNI_MoveBg_c cloth_move_bg[mNW_CLOTH_DESIGN_NUM];
    /* 0x2E8 */ aNI_MoveBg_c umbrella_move_bg[mNW_UMBRELLA_DESIGN_NUM];
    /* 0x3E8 */ aNI_Clip_c clip;
};

extern ACTOR_PROFILE Needlework_Indoor_Profile;

#ifdef __cplusplus
}
#endif

#endif
