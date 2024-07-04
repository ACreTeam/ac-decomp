#ifndef AC_TRAIN_WINDOW_H
#define AC_TRAIN_WINDOW_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*TRAIN_WINDOW_DRAW_TYPE)(ACTOR*, GAME*);

#define CRV_DEBUG_LOD_VALUE 87
#define CRV_DEBUG_RED_VALUE 88
#define CRV_DEBUG_GREEN_VALUE 89
#define CRV_DEBUG_BLUE_VALUE 90

typedef struct train_window_s {
    ACTOR actor_class;
    TRAIN_WINDOW_DRAW_TYPE draw_type;
    s16 pallete_id;
    int unk17C;
    u16* current_pallete;
    u32 Single_Scrollx;
    u32 Single_Scrolly;
    u32 Two_Scrollx1;
    u32 Two_Scrolly1;
    u32 Two_Scrollx2;
    u32 Two_Scrolly2;
    int TreeScrollx;
    int TreeScrolly;
    f32 xlu_alpha;
    f32 scroll_speed;
    s_xyz pos;
    f32 lod_factor;
} TRAIN_WINDOW_ACTOR;

extern ACTOR_PROFILE Train_Window_Profile;

#ifdef __cplusplus
}
#endif

#endif
