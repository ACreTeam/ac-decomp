#ifndef M_HANIWAPORTRAIT_OVL_H
#define M_HANIWAPORTRAIT_OVL_H

#include "types.h"
#include "m_haniwaPortrait_ovl_h.h"
#include "m_submenu_ovl.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*mHP_SET_HANIWAPORTRAIT_PROC)(Submenu*, mSM_MenuInfo_c*, GRAPH*, GAME*, f32, f32);
typedef void (*mHP_HANIWAPORTRAIT_SHAPE_MOVE_PROC)(Submenu*);

struct haniwaPortrait_ovl_s {
    cKF_SkeletonInfo_R_c keyframe;
    s_xyz keyframe_work[8];
    s_xyz keyframe_morph[8];
    u8 _0D0[72];
    mHP_SET_HANIWAPORTRAIT_PROC set_haniwaPortrait_proc;
    mHP_HANIWAPORTRAIT_SHAPE_MOVE_PROC haniwaPortrait_shape_move_proc;
};

extern void mHP_haniwaPortrait_ovl_construct(Submenu* submenu);
extern void mHP_haniwaPortrait_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
