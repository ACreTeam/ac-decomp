#ifndef ROOM_TYPE_H
#define ROOM_TYPE_H

#include "types.h"
#include "libu64/gfxprint.h"

enum {
  FG_ITEM0_TYPE,
  FG_FTR0_TYPE,
  FG_ITEM1_TYPE,
  FG_FTR1_TYPE,
  FG_NXGT0_TYPE,
  FG_STRUCTURE_TYPE,
  FG_PAD6_TYPE,
  FG_PAD7_TYPE,
  FG_ITEM2_TYPE,
  FG_ACTOR_TYPE,
  FG_PROPS_TYPE,
  FG_PAD11_TYPE,
  FG_PAD12_TYPE,
  FG_SP_NPC_TYPE,
  FG_NPC_TYPE,
  FG_DONT_TYPE,
  FG_TYPE_NUM
};

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

#define GET_FG_ITEM0_CATEGORY(f) (((f)&0x800) >> 11)
#define GET_FG_ITEM1_CATEGORY(f) (((f)&0xF00) >> 8)
#define GET_FG_TYPE(f) (((f)&0xF000) >> 12)

extern void mRmTp_DrawFamicomInfo(gfxprint_t* gfxprint);
extern void mRmTp_MakeFamicom_Fdebug();

#endif