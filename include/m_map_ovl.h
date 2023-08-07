#ifndef M_MAP_OVL_H
#define M_MAP_OVL_H

#include "types.h"
#include "m_map_ovl_h.h"
#include "m_submenu_ovl.h"
#include "m_private.h"
#include "m_collision_bg.h"
#include "m_field_make.h"
#include "PreRender.h"
#include "m_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mMP_RESIDENTS_PER_BLOCK_MAX 4
#define mMP_BLOCKX_MAX 6
#define mMP_BLOCKZ_MAX 7

#define mMP_CURSOR_FRAMES 18
#define mMP_LABEL_WORD_NUM 2

#define mMP_BLOCK_SIZE_F 22.0f

enum label_type {
  mMP_LABEL_NPC,
  mMP_LABEL_PLAYER,
  mMP_LABEL_SHOP,
  mMP_LABEL_POLICE,
  mMP_LABEL_POST,
  mMP_LABEL_SHRINE,
  mMP_LABEL_STATION,
  mMP_LABEL_JUNK,
  mMP_LABEL_MUSEUM,
  mMP_LABEL_NEEDLE,
  mMP_LABEL_PORT,

  mMP_LABEL_NUM
};

typedef struct map_resident_info_s {
  u8 name[PLAYER_NAME_LEN];
  s8 sex;
  u8 house_layer;
  u8 house_idx;
} mMP_ResidentInfo_c;

typedef struct map_labelinfo_s {
  mMP_ResidentInfo_c* residents[mMP_RESIDENTS_PER_BLOCK_MAX];
  s16 label_cnt;
  s16 label_no;
} mMP_LabelInfo_c;

typedef struct map_house_pos_entry_s {
  u8 ut_x;
  u8 ut_z;

  u8 idx;
} mMP_HousePos_Entry_c;

typedef struct map_house_pos_s {
  mActor_name_t fgblock_name;
  mMP_HousePos_Entry_c entries[3];
} mMP_HousePos_c;

typedef struct map_label_word_s {
  f32 ofs_x;
  f32 ofs_y;

  u8* str;
  int str_len;
} mMP_LabelWord_c;

typedef struct map_label_s {
  f32 ofs_x;
  f32 ofs_y;

  Gfx* gfx;
  mMP_LabelWord_c* words[mMP_LABEL_WORD_NUM];
} mMP_Label_c;

struct map_overlay_s {
  u8 sel_bx;
  u8 sel_bz;

  u8 player_bx;
  u8 player_bz;

  f32 map_cursor_current_xpos;
  f32 map_cursor_current_zpos;

  f32 map_cursor_target_xpos;
  f32 map_cursor_target_zpos;

  int cursor_frame;

  int unk_18[2];

  u8* map_texture[FG_BLOCK_TOTAL_NUM];
  u8 map_pal[FG_BLOCK_TOTAL_NUM];

  mFM_combo_info_c* combination_table;
  
  mMP_ResidentInfo_c player_info[PLAYER_NUM];
  mMP_ResidentInfo_c animal_info[ANIMAL_NUM_MAX];

  mMP_LabelInfo_c label_info[FG_BLOCK_Z_NUM][FG_BLOCK_X_NUM];

  int unk_3E8[2];

  u8 land_name_str_len;
  int unk_3F4;
};

extern void mMP_map_ovl_set_proc(Submenu* submenu);
extern void mMP_map_ovl_construct(Submenu* submenu);
extern void mMP_map_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
