#ifndef M_SCENE_TABLE_H
#define M_SCENE_TABLE_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

enum field_draw_type {
  FIELD_DRAW_TYPE_OUTDOORS,
  FIELD_DRAW_TYPE_INDOORS,
  FIELD_DRAW_TYPE_TRAIN,
  FIELD_DRAW_TYPE_PLAYER_SELECT,

  FIELD_DRAW_TYPE_NUM
};

/*
  TODO: is this right? I assume so based on file names but
  there may be a better place for this
*/

enum scene_table {
  SCENE_TEST1,
  SCENE_TEST2,
  SCENE_TEST3,
  SCENE_WATER_TEST,
  SCENE_FOOTPRINT_TEST,
  SCENE_NPC_TEST,
  SCENE_NPC_HOUSE, /* npc house interior */
  SCENE_FG, /* outdoors/FG */
  SCENE_RANDOM_NPC_TEST,
  SCENE_SHOP0 = 0x09, /* nook's cranny */
  SCENE_BROKER_SHOP = 0x0C, /* crazy redd's tent */
  SCENE_POST_OFFICE = 0x0E, /* post office */
  SCENE_START_DEMO = 0x0F, /* after player select */
  SCENE_START_DEMO2 = 0x10, /*  */
  SCENE_BUGGY = 0x12,
  SCENE_PLAYERSELECT = 0x13,
  SCENE_CONVENI = 0x17, /* nook 'n' go */
  SCENE_SUPER = 0x18, /* nookway */
  SCENE_DEPART = 0x19, /* nookington's 1st floor */
  SCENE_DEPART_2 = 0x1D, /* nookington's 2nd floor */
  SCENE_TITLE_DEMO = 0x21, /* title screen demo */
  SCENE_PLAYERSELECT_SAVE = 0x22,
  SCENE_MUSEUM_ENTRANCE = 0x23,
  SCENE_MUSEUM_ROOM = 0x24,
  SCENE_NEEDLEWORK = 0x2E, /* able sister's */
  SCENE_COTTAGE_MY = 0x2F,
  SCENE_COTTAGE_NPC = 0x30,
  /* TODO: finish */
};

#ifdef __cplusplus
}
#endif

#endif
