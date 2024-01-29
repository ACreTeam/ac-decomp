#ifndef AC_KOINOBORI_H
#define AC_KOINOBORI_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Koinobori_Profile;

typedef void (*KOINOBORI_PROC)(ACTOR*, GAME*);

/* sizeof(KOINOBORI_ACTOR) == 0x2DC */
typedef struct actor_koinobori_s{
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ int _174; // Unused
    /* 0x178 */ cKF_SkeletonInfo_R_c keyframe;
    /* 0x1E8 */ int _1E8; // Unused
    /* 0x1EC */ s_xyz work[15];
    /* 0x246 */ s_xyz morph[15];
    /* 0x2A0 */ KOINOBORI_PROC action_proc;
    /* 0x2A4 */ u8 _2A4[0x2B4 - 0x2A4]; // Unused
    /* 0x2B4 */ int action;
    /* 0x2B8 */ u8 _2B8[0x2DC - 0x2B8]; // Unused
} KOINOBORI_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

