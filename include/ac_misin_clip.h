#ifndef AC_MISIN_CLIP_H
#define AC_MISIN_CLIP_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*aMSN_REQUEST_MISIN_STOP_PROC)(void);
typedef void (*aMSN_REQUEST_MISIN_MOVE_PROC)(void);

typedef void (*aMSN_REQUEST_DUSTCLOTH_STOP_PROC)(void);
typedef void (*aMSN_REQUEST_DUSTCLOTH_MOVE_PROC)(void);

typedef struct misin_clip_s {
    ACTOR* misin_actor_p;
    aMSN_REQUEST_MISIN_STOP_PROC request_misin_stop_proc;
    aMSN_REQUEST_MISIN_MOVE_PROC request_misin_move_proc;
    aMSN_REQUEST_DUSTCLOTH_STOP_PROC request_dustcloth_stop_proc;
    aMSN_REQUEST_DUSTCLOTH_MOVE_PROC request_dustcloth_move_proc;
} aMSN_Clip_c;

#ifdef __cplusplus
}
#endif

#endif /* AC_MISIN_CLIP_H */
