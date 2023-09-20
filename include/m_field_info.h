#ifndef M_FIELD_INFO_H
#define M_FIELD_INFO_H

#include "types.h"
#include "libu64/gfxprint.h"
#include "m_lib.h"
#include "m_collision_bg.h"
#include "m_field_make.h"

#ifdef __cplusplus
extern "C" {
#endif

/* acre unit world size */
#define mFI_UT_WORLDSIZE_X 40
#define mFI_UT_WORLDSIZE_Z 40

#define mFI_UT_WORLDSIZE_X_F ((f32)mFI_UT_WORLDSIZE_X)
#define mFI_UT_WORLDSIZE_Z_F ((f32)mFI_UT_WORLDSIZE_Z)

#define mFI_UT_WORLDSIZE_HALF_X_F (mFI_UT_WORLDSIZE_X_F / 2.0f)
#define mFI_UT_WORLDSIZE_HALF_Z_F (mFI_UT_WORLDSIZE_X_F / 2.0f)

#define mFI_BK_WORLDSIZE_X_F (mFI_UT_WORLDSIZE_X_F * UT_X_NUM)
#define mFI_BK_WORLDSIZE_Z_F (mFI_UT_WORLDSIZE_Z_F * UT_Z_NUM)

#define mFI_ROW_TO_CHARSTR(row) ((row) + 'A')
#define mFI_COL_TO_CHARSTR(col) ((col) + '0')

#define mFI_NUM_SOUND_SOURCES 6

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

enum field_type2 {
  mFI_FIELDTYPE2_FG,
  mFI_FIELDTYPE2_PLAYER_ROOM,
  mFI_FIELDTYPE2_NPC_ROOM,
  mFI_FIELDTYPE2_ROOM,

  mFI_FIELDTYPE2_NUM
};

#define mFI_TO_FIELD_ID(type, index) (((type) << 12) | (index))
#define mFI_GET_TYPE(field_id) ((field_id) & 0xF000)
#define mFI_TYPE(type) ((type) << 12)

enum field_room {
  /* TODO: others */
  mFI_FIELD_FG = mFI_TO_FIELD_ID(mFI_FIELDTYPE_FG, 0),

  mFI_FIELD_ROOM0 = mFI_TO_FIELD_ID(mFI_FIELDTYPE_ROOM, 0),

  mFI_FIELD_NPCROOM0 = mFI_TO_FIELD_ID(mFI_FIELDTYPE_NPC_ROOM, 0),

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

/* "wade" between acres (acre transition) */
enum player_wade_state {
  mFI_WADE_NONE,
  mFI_WADE_START,
  mFI_WADE_INPROGRESS,
  mFI_WADE_END
};

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

typedef struct block_table_s {
  s8 block_x;
  s8 block_z;

  f32 pos_x;
  f32 pos_z;

  mActor_name_t* items;
} mFI_block_tbl_c;

enum {
  mFI_SOUND_SOURCE_POND = 3, // TODO: might not be correct name
};

typedef struct sound_source_info_s {
  s16 kind;
  xyz_t wpos;
} mFI_sound_source_info_c;



extern int mFI_CheckFieldData();
extern mActor_name_t mFI_GetFieldId();
extern int mFI_GetClimate();
extern void mFI_SetClimate(int climate);
extern mActor_name_t* mFI_BkNumtoUtFGTop(int block_x, int block_z);
extern void mFI_ClearDeposit(int block_x, int block_z);
extern int mFI_GetLineDeposit(u16* deposit, int ut_x);
extern u16* mFI_GetDepositP(int block_x, int block_z);
extern void mFI_GetSpecialBlockNum(int* block_pos_tbl, u32* kind_list, int kind_num);
extern int mFI_SetTreasure(int* block_x, int* block_z, mActor_name_t item_no);
extern void mFI_SetFGUpData();
extern int mFI_ClearBlockItemRandom_common(mActor_name_t item_no, int count, mActor_name_t* fg_items, u16* deposit, int include_deposited);
extern int mFI_Wpos2BlockNum(int* block_x, int* block_z, xyz_t world_pos);
extern int mFI_CheckPlayerWade(int wade_state);
extern void mFI_BkandUtNum2Wpos(xyz_t* wpos_p, int block_x, int block_z, int ut_x, int ut_z);
extern void mFI_BkandUtNum2CenterWpos(xyz_t* wpos_p, int block_x, int block_z, int ut_x, int ut_z);
extern mCoBG_Collision_u* mFI_GetBkNum2ColTop(int block_x, int block_z);
extern u32 mFI_BkNum2BlockKind(int block_x, int block_z);
extern int mFI_BlockKind2BkNum(int* block_x, int* block_z, u32 block_kind);
extern int mFI_GetBlockUtNum2FG(mActor_name_t* fg_item, int block_x, int block_z, int ut_x, int ut_z);
extern void mFI_UtNum2CenterWpos(xyz_t* wpos, int ut_x, int ut_z);
extern u8 mFI_GetBlockXMax();
extern u8 mFI_GetBlockZMax();
extern u8 mFI_BkNum2BlockType(int block_x, int block_z);
extern mFI_sound_source_info_c* mFI_GetSoundSourcePBlockNum(int block_x,int block_z);
extern int mFI_Wpos2UtNum(int* ut_x, int* ut_z, xyz_t wpos);
extern void mFI_ClearFieldData();
extern int mFI_SetFG_common(mActor_name_t item, xyz_t wpos, int update);
extern mActor_name_t* mFI_GetUnitFG(xyz_t wpos);
extern void mFI_Wpos2DepositOFF(xyz_t wpos);
extern mActor_name_t mFI_GetOtherFruit();
extern int mFI_Wpos2UtNum_inBlock(int* ut_x, int* ut_z, xyz_t wpos);
extern int mFI_GetItemNumInBlock(mActor_name_t item_no, mActor_name_t* block_items);
extern int mFI_BkNum2WposXZ(f32* wpos_x, f32* wpos_z, int block_x, int block_z);
extern void mFI_SetBearActor(GAME_PLAY* play, xyz_t wpos, int update_before_block_table);
extern void mFI_FieldMove(xyz_t player_wpos);
extern int mFI_search_unit_around(xyz_t* wpos, mActor_name_t item);
extern void mFI_BlockDepositOFF(u16* deposit, int ut_x, int ut_z);
extern void mFI_PullTanukiPathTrees();
extern int mFI_CheckBlockKind_OR(int block_x, int block_z, u32 kind);
extern void mFI_GetIslandBlockNumX(int* island_block_x_nums);
extern void mFI_LposInBKtoWpos(xyz_t* wpos, xyz_t lpos, int block_x, int block_z);
extern f32 mFI_GetBlockWidth();
extern f32 mFI_GetBlockHeight();
extern int mFI_Wpos2BkandUtNuminBlock(int* block_x, int* block_z, int* ut_x, int* ut_z, xyz_t wpos);
extern int mFI_GetItemNumOnBlockInField(int block_x, int block_z, mActor_name_t start_item, mActor_name_t end_item);
extern int mFI_CheckShopFieldName(mActor_name_t field_name);
extern int mFI_GetMoveActorListIdx(mFM_move_actor_c* move_actor_list, int list_size, mActor_name_t name);
extern int mFI_GetNowPlayerHouseFloorNo();
extern int mFI_BlockUtNumtoFGSet(mActor_name_t item, int bx, int bz, int ut_x, int ut_z);
extern void mFI_InitMoveActorBitData();
extern void mFI_ClearColKeep();
extern void mFI_InitAreaInfo();
extern void mFI_InitRegisterBgInfo();
extern mFM_block_info_c* mFI_GetBlockTopP();
extern int mFI_GetBlockNum(int block_x, int block_z);

extern void mFI_PrintNowBGNum(gfxprint_t* gfxprint);
extern void mFI_PrintFgAttr(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
