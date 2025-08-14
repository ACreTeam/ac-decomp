#ifndef M_FIELD_INFO_H
#define M_FIELD_INFO_H

#include "types.h"
#include "libu64/gfxprint.h"
#include "m_lib.h"
#include "m_collision_bg.h"
#include "m_field_make.h"
#include "m_bg_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/* acre unit world size */
#define mFI_UNIT_BASE_SIZE 40
#define mFI_UNIT_BASE_SIZE_F ((f32)mFI_UNIT_BASE_SIZE)

#define mFI_UT_WORLDSIZE_X mFI_UNIT_BASE_SIZE
#define mFI_UT_WORLDSIZE_Z mFI_UNIT_BASE_SIZE

#define mFI_UT_WORLDSIZE_X_F ((f32)mFI_UT_WORLDSIZE_X)
#define mFI_UT_WORLDSIZE_Z_F ((f32)mFI_UT_WORLDSIZE_Z)

#define mFI_UT_WORLDSIZE_HALF_X_F (mFI_UT_WORLDSIZE_X_F / 2.0f)
#define mFI_UT_WORLDSIZE_HALF_Z_F (mFI_UT_WORLDSIZE_X_F / 2.0f)

#define mFI_BK_WORLDSIZE_BASE (mFI_UNIT_BASE_SIZE * UT_BASE_NUM)
#define mFI_BK_WORLDSIZE_BASE_F ((f32)mFI_BK_WORLDSIZE_BASE)

#define mFI_BK_WORLDSIZE_X mFI_BK_WORLDSIZE_BASE
#define mFI_BK_WORLDSIZE_Z mFI_BK_WORLDSIZE_BASE

#define mFI_BK_WORLDSIZE_X_F mFI_BK_WORLDSIZE_BASE_F
#define mFI_BK_WORLDSIZE_Z_F mFI_BK_WORLDSIZE_BASE_F

#define mFI_BK_WORLDSIZE_HALF_X (mFI_BK_WORLDSIZE_X / 2)
#define mFI_BK_WORLDSIZE_HALF_Z (mFI_BK_WORLDSIZE_Z / 2)

#define mFI_BK_WORLDSIZE_HALF_X_F (mFI_BK_WORLDSIZE_X_F / 2.0f)
#define mFI_BK_WORLDSIZE_HALF_Z_F (mFI_BK_WORLDSIZE_Z_F / 2.0f)

#define mFI_POS2UT(pos) ((int)((pos) / mFI_UNIT_BASE_SIZE_F))
#define mFI_BK_UT_2_POS(bk, ut) (((bk) * UT_BASE_NUM + (ut)) * mFI_UNIT_BASE_SIZE_F)

#define mFI_ROW_TO_CHARSTR(row) ((row) + 'A')
#define mFI_COL_TO_CHARSTR(col) ((col) + '0')

#define mFI_NUM_COL_KEEP 9
#define mFI_NUM_SOUND_SOURCES 6
#define mFI_SET_SHELL_NUM 20
#define mFI_MAX_SHELLS_PER_BLOCK 4

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
    mFI_FIELD_ROOM_SHOP0,           /* 0x3001 */
    mFI_FIELD_ROOM_BROKER_SHOP,     /* 0x3002 */
    mFI_FIELD_ROOM_POST_OFFICE,     /* 0x3003 */
    mFI_FIELD_ROOM_POLICE_BOX,      /* 0x3004 */
    mFI_FIELD_ROOM_BUGGY,           /* 0x3005 */
    mFI_FIELD_ROOM_SHOP1,           /* 0x3006 */
    mFI_FIELD_ROOM_SHOP2,           /* 0x3007 */
    mFI_FIELD_ROOM_SHOP3_1,         /* 0x3008 */
    mFI_FIELD_ROOM_SHOP3_2,         /* 0x3009 */
    mFI_FIELD_ROOM_KAMAKURA,        /* 0x300A */
    mFI_FIELD_ROOM_MUSEUM_ENTRANCE, /* 0x300B */
    mFI_FIELD_ROOM_MUSEUM_PAINTING, /* 0x300C */
    mFI_FIELD_ROOM_MUSEUM_FOSSIL,   /* 0x300D */
    mFI_FIELD_ROOM_MUSEUM_INSECT,   /* 0x300E */
    mFI_FIELD_ROOM_MUSEUM_FISH,     /* 0x300F */
    mFI_FIELD_ROOM_NEEDLEWORK,      /* 0x3010 */
    mFI_FIELD_ROOM_LIGHTHOUSE,      /* 0x3011 */
    mFI_FIELD_ROOM_TENT,            /* 0x3012 */

    mFI_FIELD_NPCROOM0 = mFI_TO_FIELD_ID(mFI_FIELDTYPE_NPC_ROOM, 0),
    mFI_FIELD_NPCROOM_FIELD_TOOL_INSIDE,

    mFI_FIELD_DEMO_STARTDEMO = mFI_TO_FIELD_ID(mFI_FIELDTYPE_DEMO, 0),
    mFI_FIELD_DEMO_STARTDEMO2,
    mFI_FIELD_DEMO_PLAYERSELECT,
    mFI_FIELD_DEMO_STARTDEMO3,

    mFI_FIELD_PLAYER0_ROOM = mFI_TO_FIELD_ID(mFI_FIELDTYPE_PLAYER_ROOM, 0),
    mFI_FIELD_PLAYER1_ROOM,
    mFI_FIELD_PLAYER2_ROOM,
    mFI_FIELD_PLAYER3_ROOM,

    /* TODO: others */
};

#define mFI_GET_PLAYER_ROOM_NO(field_id) (((field_id) - mFI_FIELD_PLAYER0_ROOM) & 3)
#define mFI_IS_PLAYER_ROOM(field_id)                                                 \
    ((field_id) == mFI_FIELD_PLAYER0_ROOM || (field_id) == mFI_FIELD_PLAYER1_ROOM || \
     (field_id) == mFI_FIELD_PLAYER2_ROOM || (field_id) == mFI_FIELD_PLAYER3_ROOM)

/* "wade" between acres (acre transition) */
enum player_wade_state {
    mFI_WADE_NONE,
    mFI_WADE_START,
    mFI_WADE_INPROGRESS,
    mFI_WADE_END,
    mFI_WADE_ERROR,

    mFI_WADE_NUM
};

enum {
    mFI_DEPOSIT_ON,
    mFI_DEPOSIT_OFF,
    mFI_DEPOSIT_GET,

    mFI_DEPOSIT_NUM
};

enum {
    mFI_MOVEDIR_NONE,
    mFI_MOVEDIR_RIGHT,
    mFI_MOVEDIR_LEFT,
    mFI_MOVEDIR_UP,
    mFI_MOVEDIR_DOWN,

    mFI_MOVEDIR_NUM
};

/* Not sure about these other than the island one */
enum {
    mFI_CLIMATE_0,
    mFI_CLIMATE_ISLAND,
    mFI_CLIMATE_2,
    mFI_CLIMATE_3,
    mFI_CLIMATE_4,
    mFI_CLIMATE_5,

    mFI_CLIMATE_NUM,
};

enum {
    mFI_DIGSTATUS_MISS,
    mFI_DIGSTATUS_CANCEL,
    mFI_DIGSTATUS_FILLIN,
    mFI_DIGSTATUS_DIG,
    mFI_DIGSTATUS_PUT_ITEM,
    mFI_DIGSTATUS_GET_ITEM,

    mFI_DIGSTATUS_NUM
};

enum {
    mFI_SET_STRUCTURE_SET,
    mFI_SET_STRUCTURE_REMOVE,

    mFI_SET_STRUCTURE_NUM
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

typedef struct visible_block_item_info_s {
    int count;
    mFI_block_tbl_c block_info_tbl[mFM_VISIBLE_BLOCK_NUM];
} mFI_item_table_c;

enum {
    mFI_SOUND_SOURCE_NONE,
    mFI_SOUND_SOURCE_RIVER,
    mFI_SOUND_SOURCE_OCEAN,
    mFI_SOUND_SOURCE_POND,

    mFI_SOUND_SOURCE_NUM
};

extern void mFI_ClearFieldData();
extern int mFI_CheckFieldData();
extern mFM_block_info_c* mFI_GetBlockTopP();
extern mActor_name_t mFI_GetFieldId();
extern int mFI_CheckShopFieldName(mActor_name_t field_name);
extern int mFI_CheckShop();
extern u8 mFI_GetBlockXMax();
extern u8 mFI_GetBlockZMax();
extern f32 mFI_GetBlockWidth();
extern f32 mFI_GetBlockHeight();
extern int mFI_GetBlockNum(int block_x, int block_z);
extern int mFI_BlockCheck(int block_x, int block_z);
extern int mFI_UtNumCheck(int ut_x, int ut_z, int bx_max, int bz_max);
extern int mFI_WposX2UtNumX(f32 wpos_x);
extern int mFI_WposZ2UtNumZ(f32 wpos_z);
extern int mFI_Wpos2UtNum(int* ut_x, int* ut_z, xyz_t wpos);
extern int mFI_UtNum2CenterWpos(xyz_t* wpos, int ut_x, int ut_z);
extern int mFI_Wpos2UtCenterWpos(xyz_t* wpos, xyz_t src_pos);
extern int mFI_Wpos2UtNum_inBlock(int* ut_x, int* ut_z, xyz_t wpos);
extern int mFI_Wpos2BlockNum(int* bx, int* bz, xyz_t wpos);
extern int mFI_Wpos2BkandUtNuminBlock(int* bx, int* bz, int* ut_x, int* ut_z, xyz_t wpos);
extern int mFI_WpostoLposInBK(xyz_t* lpos, xyz_t wpos);
extern int mFI_LposInBKtoWpos(xyz_t* wpos, xyz_t lpos, int bx, int bz);
extern int mFI_ScrollCheck(xyz_t wpos, u8 dir);
extern int mFI_BkNum2WposXZ(f32* wpos_x, f32* wpos_z, int bx, int bz);
extern void mFI_UtNum2PosXZInBk(f32* pos_x, f32* pos_z, int ut_x, int ut_z);
extern void mFI_BkandUtNum2Wpos(xyz_t* wpos, int bx, int bz, int ut_x, int ut_z);
extern void mFI_BkandUtNum2CenterWpos(xyz_t* wpos, int bx, int bz, int ut_x, int ut_z);
extern mFM_field_draw_info_c* mFI_BGDisplayListTop();
extern mFM_field_pal_c* mFI_GetFieldPal();
extern int mFI_GetPlayerHouseFloorNo(int scene);
extern int mFI_GetNowPlayerHouseFloorNo();
extern void mFI_InitRegisterBgInfo();
extern int mFI_CheckBgDma(int bx, int bz);
extern f32 mFI_UtNum2BaseHeight(int ut_x, int ut_z);
extern f32 mFI_BkNum2BaseHeight(int bx, int bz);
extern u8 mFI_BkNum2BlockType(int bx, int bz);
#if VERSION != VER_GAFU01_00
extern int mFI_GetPuleIdx();
#else
extern int mFI_GetPoolIdx();
#define mFI_GetPuleIdx() mFI_GetPoolIdx()
#endif
extern u32 mFI_BkNum2BlockKind(int bx, int bz);
extern int mFI_CheckBlockKind(int bx, int bz, u32 block_kind);
extern int mFI_CheckBlockKind_OR(int bx, int bz, u32 block_kind_OR);
extern int mFI_BlockKind2BkNum(int* bx, int* bz, u32 kind);
extern void mFI_GetSpecialBlockNum(int* block_pos, u32* kinds, int count);
extern void mFI_GetIslandBlockNumX(int* island_x_blocks);
extern mCoBG_Collision_u* mFI_GetBkNum2ColTop(int bx, int bz);
extern mCoBG_Collision_u* mFI_UtNum2UtCol(int ut_x, int ut_z);
extern void mFI_ClearColKeep();
extern mCoBG_Collision_u* mFI_GetUnitCol(xyz_t wpos);
extern u8 mFI_UtNum2UtKeepH(int ut_x, int ut_z);
extern mFM_bg_sound_source_c* mFI_GetSoundSourcePBlockNum(int bx, int bz);
extern Gfx* mFI_GetBGDisplayListRom(int bx, int bz);
extern Gfx* mFI_GetBGDisplayListRom_XLU(int bx, int bz);
extern EVW_ANIME_DATA* mFI_GetBGTexAnimInfo(s8* anim_num, int bx, int bz);
extern void mFI_InitAreaInfo();
extern void mFI_BGDisplayListRefresh(xyz_t wpos);
extern int mFI_CheckInIsland();
extern int mFI_CheckInJustIslandOutdoor();
extern u32 mFI_CheckPlayerBlockInfo();
extern mActor_name_t* mFI_BkNumtoUtFGTop(int bx, int bz);
extern mActor_name_t* mFI_BkNum2UtFGTop_layer(int bx, int bz, int layer);
extern mActor_name_t* mFI_UtNum2UtFG(int ut_x, int ut_z);
extern mActor_name_t* mFI_GetUnitFG(xyz_t wpos);
extern mActor_name_t* mFI_GetUnitFG2(xyz_t wpos);
extern int mFI_GetBlockUtNum2FG(mActor_name_t* item, int bx, int bz, int ut_x, int ut_z);
extern int mFI_BlockUtNumtoFGSet(mActor_name_t item, int bx, int bz, int ut_x, int ut_z);
extern int mFI_UtNumtoFGSet_common(mActor_name_t item, int ut_x, int ut_z, int update);
extern int mFI_SetFG_common(mActor_name_t item, xyz_t wpos, int update);
extern int mFI_SetFG2(mActor_name_t item, xyz_t wpos);
extern void mFI_InitItemTable(mFI_item_table_c* vis_block_info);
extern int mFI_GetOldItemTableIdx(int n);
extern int mFI_GetItemTable_NoReset(mFI_item_table_c* item_table, xyz_t wpos);
extern int mFI_GetItemTable(mFI_item_table_c* item_table, xyz_t wpos, char* file, int line);
extern int mFI_FGisUpDate();
extern void mFI_SetFGUpData();
extern void mFI_BornItemON();
// extern MATCH_FORCESTRIP void mFI_BornItemOFF();
extern int mFI_ItemisBorn();
extern int mFI_ActorisBorn();
extern void mFI_SetBearActor(GAME_PLAY* play, xyz_t wpos, int set_flag);
extern int mFI_search_unit_around(xyz_t* wpos, mActor_name_t item);
extern MATCH_FORCESTRIP int mFI_search_unit_around2(xyz_t* wpos, mActor_name_t item);
extern int mFI_GetItemNumOnBlock(int bx, int bz, mActor_name_t min_item, mActor_name_t max_item);
extern int mFI_GetItemNumOnBlockInField(int bx, int bz, mActor_name_t min_item, mActor_name_t max_item);
extern int mFI_GetItemNumField_BCT(mActor_name_t min_item, mActor_name_t max_item);
extern int mFI_GetItemNumField(mActor_name_t min_item, mActor_name_t max_item);
extern int mFI_GetItemNumInBlock(mActor_name_t item, mActor_name_t* fg_items);
extern int mFI_SearchFGInBlock(int* ut_x, int* ut_z, mActor_name_t item, int bx, int bz);
extern int mFI_CheckFGExist(mActor_name_t* check_items, int check_item_num);
extern u8* mFI_GetHaniwaStepBlock(int bx, int bz);
extern u16 mFI_GetMoveActorBitData(int bx, int bz);
extern void mFI_SetMoveActorBitData(int bx, int bz, u16 move_actor_bit_data);
extern void mFI_SetMoveActorBitData_ON(s16 move_actor_idx, int bx, int bz);
extern void mFI_SetMoveActorBitData_OFF(s16 move_actor_idx, int bx, int bz);
extern void mFI_MyMoveActorBitData_ON(ACTOR* actor);
// extern MATCH_FORCESTRIP void mFI_MyMoveActorBitData_OFF(ACTOR* actor);
extern int mFI_GetMoveActorListIdx(mFM_move_actor_c* move_actor_list, int list_size, mActor_name_t actor_name);
extern int mFI_RegistMoveActorList(mActor_name_t actor_name, int bx, int bz, int ut_x, int ut_z, int npc_info_idx,
                                   s16 arg);
extern int mFI_UnregistMoveActorList(mActor_name_t actor_name, int bx, int bz);
extern int mFI_AddMoveActorList(mActor_name_t actor_name, int bx, int bz, int ut_x, int ut_z, s16 arg);
extern mFM_move_actor_c* mFI_MoveActorListDma(int bx, int bz);
extern void mFI_InitMoveActorBitData();
extern void mFI_SetPlayerWade(GAME* game);
extern int mFI_CheckPlayerWade(int wade);
extern int mFI_GetPlayerWade();
extern int mFI_GetNextBlockNum(int* bx, int* bz);
extern u16* mFI_GetDepositP(int bx, int bz);
extern void mFI_ClearDeposit(int bx, int bz);
extern int mFI_GetLineDeposit(u16* deposit, int ut_x);
// extern MATCH_FORCESTRIP void mFI_BlockDepositON(u16* deposit_p, int ut_x, int ut_z);
extern void mFI_BlockDepositOFF(u16* deposit_p, int ut_x, int ut_z);
extern int mFI_GetBlockDeposit(u16* deposit_p, int ut_x, int ut_z);
// extern MATCH_FORCESTRIP void mFI_BkUtNum2DepositON(int bx, int bz, int ut_x, int ut_z);
extern void mFI_BkUtNum2DepositOFF(int bx, int bz, int ut_x, int ut_z);
// extern MATCH_FORCESTRIP int mFI_BkUtNum2DepositGet(int bx, int bz, int ut_x, int ut_z);
extern void mFI_UtNum2DepositON(int ut_x, int ut_z);
extern void mFI_UtNum2DepositOFF(int ut_x, int ut_z);
extern int mFI_UtNum2DepositGet(int ut_x, int ut_z);
extern void mFI_Wpos2DepositON(xyz_t wpos);
extern void mFI_Wpos2DepositOFF(xyz_t wpos);
extern int mFI_Wpos2DepositGet(xyz_t wpos);
extern int mFI_CheckItemNoHole(mActor_name_t item);
/* @unused extern int mFI_CheckCanDeposit(xyz_t wpos?) */
extern int mFI_GetDigStatus(mActor_name_t* item, xyz_t wpos, int golden_shovel);
extern void mFI_ClearHoleBlock(int bx, int bz);
extern void mFI_ClearBeecomb(int bx, int bz);
extern int mFI_SetFGStructure_common(mActor_name_t structure_name, int bx, int bz, int ut_x, int ut_z, int set_type);
extern int mFI_CheckStructureArea(int ut_x, int ut_z, mActor_name_t structure_name, int structure_ut_x,
                                  int structure_ut_z);
extern mActor_name_t mFI_GetOtherFruit();
extern int mFI_CheckFGNpcOn(mActor_name_t item);
extern int mFI_CheckLapPolice(int bx, int bz, int ut_x, int ut_z);
extern int mFI_GetWaveUtinBlock(int* ut_x, int* ut_z, int bx, int bz);
extern int mFI_ClearBlockItemRandom_common(mActor_name_t item, int clear_num, mActor_name_t* fg_p, u16* deposit_p,
                                           int delete_buried);
extern void mFI_SetFirstSetShell();
extern void mFI_FieldMove(xyz_t player_pos);
extern void mFI_PrintNowBGNum(gfxprint_t* gfxprint);
extern void mFI_PrintFgAttr(gfxprint_t* gfxprint);
extern int mFI_SetOyasiroPos(s16* oyasiro_p);
extern int mFI_SetTreasure(int* selected_bx, int* selected_bz, mActor_name_t item);
extern int mFI_GetClimate();
extern void mFI_SetClimate(int climate);
extern int mFI_CheckBeforeScenePerpetual();
extern void mFI_ChangeClimate_ForEventNotice();
extern void mFI_PullTanukiPathTrees();

#ifdef __cplusplus
}
#endif

#endif
