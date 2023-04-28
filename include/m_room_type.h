#ifndef ROOM_TYPE_H
#define ROOM_TYPE_H

#include "types.h"
#include "libu64/gfxprint.h"
#include "m_actor_type.h"

#define mRmTp_FTR_UNIT_MAX 4

enum {
  mRmTp_FTRSIZE_1x1, /* x */
  mRmTp_FTRSIZE_1x2, /* yy OR y */
                     /*       y */
  mRmTp_FTRSIZE_2x2, /* zz */
                     /* zz */
  mRmTp_FTRSIZE_NUM
};

typedef struct room_type_place_info_one_s {
  int exists;
  int ut_x;
  int ut_z;
} mRmTp_FtrPlaceInfoOne_t;

typedef struct room_type_place_info_s {
  mRmTp_FtrPlaceInfoOne_t units[mRmTp_FTR_UNIT_MAX];
} mRmTp_FtrPlaceInfo_t;

#define FTR_NUM 1266

#define FTR_GET_ROTATION(f) ((f) & 3)

// TEMPORARY. Should be generated with .decl files
#define ITEM0_NO_START 0x0000
#define NULL_NO ITEM0_NO_START
#define ITEM0_1_NO_START ITEM0_NO_START + 0x800

#define FTR0_NO_START 0x1000

#define ITEM1_NO_START 0x2000
#define ITEM1_0_NO_START ITEM0_1_NO_START        // paper
#define ITEM1_1_NO_START ITEM1_NO_START + 0x100  // money
#define ITEM1_2_NO_START ITEM1_NO_START + 0x200  // tools
#define ITEM1_3_NO_START ITEM1_NO_START + 0x300  // fish
#define ITEM1_4_NO_START ITEM1_NO_START + 0x400  // clothing
#define ITEM1_5_NO_START ITEM1_NO_START + 0x500  // etc
#define ITEM1_6_NO_START ITEM1_NO_START + 0x600  // carpets
#define ITEM1_7_NO_START ITEM1_NO_START + 0x700  // wallpaper
#define ITEM1_8_NO_START ITEM1_NO_START + 0x800  // food
#define ITEM1_9_NO_START ITEM1_NO_START + 0x900  // seeds
#define ITEM1_A_NO_START ITEM1_NO_START + 0xA00  // mini disks
#define ITEM1_B_NO_START ITEM1_NO_START + 0xB00  // diaries
#define ITEM1_C_NO_START ITEM1_NO_START + 0xC00  // tickets
#define ITEM1_D_NO_START ITEM1_NO_START + 0xD00  // insects
#define ITEM1_E_NO_START ITEM1_NO_START + 0xE00  // hukubukuro
#define ITEM1_F_NO_START ITEM1_NO_START + 0xF00  // kabu

#define FTR1_NO_START 0x3000

extern void mRmTp_DrawFamicomInfo(gfxprint_t* gfxprint);
extern void mRmTp_MakeFamicom_Fdebug();

extern int mRmTp_FtrItemNo2FtrIdx(mActor_name_t ftr_item_no);
extern int mRmTp_GetFurnitureData(mActor_name_t ftr, int ut_x, int ut_z, mRmTp_FtrPlaceInfo_t* place_info);

#endif