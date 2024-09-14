#ifndef AC_SHOP_INDOOR_H
#define AC_SHOP_INDOOR_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct shop_indoor_actor_s SHOP_INDOOR_ACTOR;

typedef int (*aSI_CHANGE_WALL_PROC)(mActor_name_t item);
typedef int (*aSI_CHANGE_CARPET_PROC)(mActor_name_t item);
typedef void (*aSI_INDOOR_DMA_AGAIN_PROC)(void);
typedef void (*aSI_CHANGE2DEFAULT_PROC)(void);

typedef struct shop_indoor_clip_s {
    ACTOR* shop_indoor_actor;
    aSI_CHANGE_WALL_PROC change_wall_proc;
    aSI_CHANGE_CARPET_PROC change_carpet_proc;
    aSI_INDOOR_DMA_AGAIN_PROC indoor_dma_again_proc;
    aSI_CHANGE2DEFAULT_PROC change2default_proc;
} aSI_Clip_c;

struct shop_indoor_actor_s {
    ACTOR actor_class;
    s16 floor_idx;
    s16 wall_idx;
    s16 floor_data_idx;
    s16 wall_data_idx;
    int _17C;
    u8* floor_data_p[2];
    u8* wall_data_p[2];
    s16 shop_idx;
    aSI_Clip_c clip;
    int fukubiki_active;
};

extern ACTOR_PROFILE Shop_Indoor_Profile;

#ifdef __cplusplus
}
#endif

#endif
