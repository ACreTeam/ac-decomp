#ifndef AC_MY_INDOOR_H
#define AC_MY_INDOOR_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aMI_PAL_SIZE (16 * sizeof(u16))
#define aMI_TEX_SIZE ((64 * 64) / 2)

#define aMI_WALL_TEX_NUM 2
#define aMI_FLOOR_TEX_NUM 4

#define aMI_WALL_BANK_SIZE (aMI_PAL_SIZE + aMI_WALL_TEX_NUM * aMI_TEX_SIZE)
#define aMI_FLOOR_BANK_SIZE (aMI_PAL_SIZE + aMI_FLOOR_TEX_NUM * aMI_TEX_SIZE)

#define aMI_STEP_TYPE_NUM 4

enum {
    aMI_BANK0,
    aMI_BANK1,

    aMI_BANK_NUM
};

typedef struct my_indoor_actor_s MY_INDOOR_ACTOR;

typedef mActor_name_t (*aMI_CHANGE_WALL_PROC)(mActor_name_t item);
typedef mActor_name_t (*aMI_CHANGE_CARPET_PROC)(mActor_name_t item);
typedef void (*aMI_INDOOR_DMA_AGAIN_PROC)();
typedef void (*aMI_CHANGE_2_DEFAULT_PROC)();
typedef mActor_name_t (*aMI_WALL_IDX_2_CHANGE_WALL_PROC)(int wall_idx, int is_original_design);
typedef mActor_name_t (*aMI_FLOOR_IDX_2_CHANGE_FLOOR_PROC)(int floor_idx, int is_original_design);

typedef struct my_room_actor_clip_s {
    MY_INDOOR_ACTOR* my_indoor_actor_p;
    aMI_CHANGE_WALL_PROC change_wall_proc;
    aMI_CHANGE_CARPET_PROC change_carpet_proc;
    aMI_INDOOR_DMA_AGAIN_PROC indoor_dma_again_proc;
    aMI_CHANGE_2_DEFAULT_PROC change_2_default_proc;
    aMI_WALL_IDX_2_CHANGE_WALL_PROC wall_idx_2_change_wall_proc;
    aMI_FLOOR_IDX_2_CHANGE_FLOOR_PROC floor_idx_2_change_floor_proc;
} aMI_Clip_c;

typedef void (*aMI_DRAW_PROC)(ACTOR*, GAME*);

typedef struct my_indoor_data_bank_s {
    int _00;
    aMI_DRAW_PROC floor_draw_proc;
    aMI_DRAW_PROC wall_draw_proc;
    u8* floor_data_p;
    u8* wall_data_p;
    int _14;
} aMI_bank_c;

typedef struct my_indoor_reserve_s {
    int reserve_flag;
    int idx;
    int is_original_flag;
} aMI_reserve_c;

struct my_indoor_actor_s {
    ACTOR actor_class;
    s16 floor_num;
    s16 wall_num;
    int floor_is_original_design;
    int wall_is_original_design;
    s16 floor_bank_idx;
    s16 wall_bank_idx;
    aMI_bank_c banks[aMI_BANK_NUM];
    int _1B4;
    aMI_Clip_c clip;
    s16 room_kind;
    aMI_reserve_c wall_reserve;
    aMI_reserve_c floor_reserve;
    int room_step[aMI_STEP_TYPE_NUM];
    int _200; // very small chance this is part of room_step
    int house_floor_no;
};

extern ACTOR_PROFILE My_Indoor_Profile;

#ifdef __cplusplus
}
#endif

#endif
