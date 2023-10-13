#ifndef AC_MY_INDOOR_H
#define AC_MY_INDOOR_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct my_indoor_actor_s MY_INDOOR_ACTOR;

typedef mActor_name_t (*aMI_CHANGE_WALL_PROC)(mActor_name_t item);
typedef mActor_name_t (*aMI_CHANGE_CARPET_PROC)(mActor_name_t item);
typedef void (*aMI_INDOOR_DMA_AGAIN_PROC)();
typedef void (*aMI_CHANGE_2_DEFAULT_PROC)();
typedef void (*aMI_WALL_IDX_2_CHANGE_WALL_PROC)(int wall_idx, int is_original_design);
typedef void (*aMI_FLOOR_IDX_2_CHANGE_FLOOR_PROC)(int floor_idx, int is_original_design);

typedef struct my_room_actor_clip_s {
  MY_INDOOR_ACTOR* my_indoor_actor_p;
  aMI_CHANGE_WALL_PROC change_wall_proc;
  aMI_CHANGE_CARPET_PROC change_carpet_proc;
  aMI_INDOOR_DMA_AGAIN_PROC indoor_dma_again_proc;
  aMI_CHANGE_2_DEFAULT_PROC change_2_default_proc;
  aMI_WALL_IDX_2_CHANGE_WALL_PROC wall_idx_2_change_wall_proc;
  aMI_FLOOR_IDX_2_CHANGE_FLOOR_PROC floor_idx_2_change_floor_proc;
} aMI_Clip_c;

typedef struct my_indoor_data_bank_s {
  u8 _00[0x0C - 0x00];
  u8* floor_data_p;
  u8* wall_data_p;
  int _14;
} aMI_bank_c;

struct my_indoor_actor_s {
  ACTOR actor_class;
  s16 floor_num;
  s16 wall_num;
  int floor_is_original_design;
  int wall_is_original_design;
  s16 floor_bank_idx;
  s16 wall_bank_idx;
  aMI_bank_c banks[2];
  int _1B4;
  aMI_Clip_c clip;
  s16 room_kind;
  int change_wall_flag;
  int reserved_wall_num;
  int reserved_wall_is_original_design;
  int change_floor_flag;
  int reserved_floor_num;
  int reserved_floor_is_original_design;
  int room_step[4];
  int _200; // very small chance this is part of room_step
  int house_floor_no;
};

extern ACTOR_PROFILE My_Indoor_Profile;

#ifdef __cplusplus
}
#endif

#endif

