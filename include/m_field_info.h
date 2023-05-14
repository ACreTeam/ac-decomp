#ifndef M_FIELD_INFO_H
#define M_FIELD_INFO_H

#include "types.h"
#include "libu64/gfxprint.h"


#ifdef __cplusplus
extern "C" {
#endif

#define mFI_ROW_TO_CHARSTR(row) ((row) + 'A')
#define mFI_COL_TO_CHARSTR(col) ((col) + '0')

enum field_type {
  mFI_FIELDTYPE_FG,
  mFI_FIELDTYPE_1,
  mFI_FIELDTYPE_2,
  mFI_FIELDTYPE_ROOM,
  mFI_FIELDTYPE_NPC_ROOM,
  mFI_FIELDTYPE_DEMO,
  mFI_FIELDTYPE_PLAYER_ROOM,

  mFI_FIELDTYPE_NUM
};

#define mFI_TO_FIELD_ID(type, index) (((type) << 12) | (index))
#define mFI_GET_TYPE(field_id) ((field_id) & 0xF000)
#define mFI_TYPE(type) ((type) << 12)

enum field_room {
  /* TODO: others */

  mFI_FIELD_PLAYER0_ROOM = mFI_TO_FIELD_ID(mFI_FIELDTYPE_PLAYER_ROOM, 0),
  mFI_FIELD_PLAYER1_ROOM,
  mFI_FIELD_PLAYER2_ROOM,
  mFI_FIELD_PLAYER3_ROOM,

  /* TODO: others */
};

#define mFI_GET_PLAYER_ROOM_NO(field_id) (((field_id)-mFI_FIELD_PLAYER0_ROOM) & 3)
#define mFI_IS_PLAYER_ROOM(field_id) \
  ((field_id) == mFI_FIELD_PLAYER0_ROOM || (field_id) == mFI_FIELD_PLAYER1_ROOM || \
   (field_id) == mFI_FIELD_PLAYER2_ROOM || (field_id) == mFI_FIELD_PLAYER3_ROOM)

/* Not sure about these other than the island one */
enum {
  mFI_CLIMATE_0,
  mFI_CLIMATE_ISLAND,
  mFI_CLIMATE_2,
  mFI_CLIMATE_3,
  mFI_CLIMATE_4,
  mFI_CLIMATE_5,
  mFI_CLIMATE_NUM
};

/* sizeof(mFI_unit_c) == 0x14 */
typedef struct location_info_s {
  /* 0x00 */ int block_x;
  /* 0x04 */ int block_z;
  /* 0x08 */ int unit_x;
  /* 0x0C */ int unit_z;
  /* 0x10 */ mActor_name_t* block_data;
} mFI_unit_c;

extern int mFI_CheckFieldData();
extern mActor_name_t mFI_GetFieldId();
extern int mFI_GetClimate();
extern mActor_name_t* mFI_BkNumtoUtFGTop(int block_x, int block_z);
extern void mFI_ClearDeposit(int block_x, int block_z);
extern void mFI_GetSpecialBlockNum(int* block_pos_tbl, u32* kind_list, int kind_num);
extern int mFI_SetTreasure(int* block_x, int* block_z, mActor_name_t item_no);

extern void mFI_PrintNowBGNum(gfxprint_t* gfxprint);
extern void mFI_PrintFgAttr(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
