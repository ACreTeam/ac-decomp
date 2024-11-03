#ifndef AC_GYO_KAGE_H
#define AC_GYO_KAGE_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Gyo_Kage_Profile;

typedef struct gyo_kage_actor_s GYO_KAGE_ACTOR;

struct gyo_kage_actor_s {
    ACTOR actor_class;
    ACTOR* gyoei_actor;
    s16 type;
    int _17C;
    ClObjPipe_c col_pipe;
    int delete_timer;
    s16 draw_frame;
    u8 exist_flag;
    u8 wall_flag;
    u32 alpha;
    int data_id;
};

#ifdef __cplusplus
}
#endif

#endif
