#ifndef AC_COMMON_H
#define AC_COMMON_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(aCM_anime_c) == 0x7C */
typedef struct actor_common_anime_s {
    /* 0x00 */ int cur_keyframe;
    /* 0x04 */ int state;
    /* 0x08 */ cKF_SkeletonInfo_R_c keyframe;
    /* 0x78 */ int anime_no;
} aCMN_anime_c;

/* sizeof(CMN_ACTOR) == 0x210 */
typedef struct actor_common_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ aCMN_anime_c anime;
    /* 0x1F0 */ ClObjPipe_c col_pipe;
    /* 0x20C */ int act;
} CMN_ACTOR;

#ifdef __cplusplus
}
#endif

#endif
