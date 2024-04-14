#ifndef M_SCENE_TABLE_H
#define M_SCENE_TABLE_H

#include "types.h"
// #include "m_scene.h"

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

typedef struct scene_status_s {
    u8 unk0[0x13];
    u8 unk13;
} Scene_data_status_c;

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
    SCENE_FG,        /* outdoors/FG */
    SCENE_RANDOM_NPC_TEST,
    SCENE_SHOP0, /* nook's cranny */
    SCENE_BG_TEST_NO_RIVER,
    SCENE_BG_TEST_RIVER,
    SCENE_BROKER_SHOP, /* crazy redd's tent */
    SCENE_FIELD_TOOL_INSIDE,
    SCENE_POST_OFFICE, /* post office */
    SCENE_START_DEMO,  /* after player select */
    SCENE_START_DEMO2, /*  */
    SCENE_POLICE_BOX,
    SCENE_BUGGY,
    SCENE_PLAYERSELECT,
    SCENE_MY_ROOM_S,
    SCENE_MY_ROOM_M,
    SCENE_MY_ROOM_L,
    SCENE_CONVENI, /* nook 'n' go */
    SCENE_SUPER,   /* nookway */
    SCENE_DEPART,  /* nookington's 1st floor */
    SCENE_TEST5,
    SCENE_PLAYERSELECT_2,
    SCENE_PLAYERSELECT_3,
    SCENE_DEPART_2, /* nookington's 2nd floor */
    SCENE_EVENT_ANNOUNCEMENT,
    SCENE_KAMAKURA,
    SCENE_FIELD_TOOL,
    SCENE_TITLE_DEMO, /* title screen demo */
    SCENE_PLAYERSELECT_SAVE,
    SCENE_MUSEUM_ENTRANCE,
    SCENE_MUSEUM_ROOM_PAINTING,
    SCENE_MUSEUM_ROOM_FOSSIL,
    SCENE_MUSEUM_ROOM_INSECT,
    SCENE_MUSEUM_ROOM_FISH,
    SCENE_MY_ROOM_LL1,
    SCENE_MY_ROOM_LL2,
    SCENE_MY_ROOM_BASEMENT_S,
    SCENE_MY_ROOM_BASEMENT_M,
    SCENE_MY_ROOM_BASEMENT_L,
    SCENE_MY_ROOM_BASEMENT_LL1,
    SCENE_NEEDLEWORK, /* able sister's */
    SCENE_COTTAGE_MY,
    SCENE_COTTAGE_NPC,
    SCENE_START_DEMO3,
    SCENE_LIGHTHOUSE,
    SCENE_TENT,

    SCENE_NUM
};

#define mSc_IS_SCENE_PLAYER_HOUSE_ROOM(scene)                                                               \
    ((scene) == SCENE_MY_ROOM_S || (scene) == SCENE_MY_ROOM_M || (scene) == SCENE_MY_ROOM_L ||              \
     (scene) == SCENE_MY_ROOM_LL1 || (scene) == SCENE_MY_ROOM_LL2 || (scene) == SCENE_MY_ROOM_BASEMENT_S || \
     (scene) == SCENE_MY_ROOM_BASEMENT_M || (scene) == (SCENE_MY_ROOM_BASEMENT_L) ||                        \
     (scene) == SCENE_MY_ROOM_BASEMENT_LL1)

#define mSc_IS_SCENE_PLAYER_ROOM(scene)                                                                     \
    ((scene) == SCENE_MY_ROOM_S || (scene) == SCENE_MY_ROOM_M || (scene) == SCENE_MY_ROOM_L ||              \
     (scene) == SCENE_MY_ROOM_LL1 || (scene) == SCENE_MY_ROOM_LL2 || (scene) == SCENE_MY_ROOM_BASEMENT_S || \
     (scene) == SCENE_MY_ROOM_BASEMENT_M || (scene) == (SCENE_MY_ROOM_BASEMENT_L) ||                        \
     (scene) == SCENE_MY_ROOM_BASEMENT_LL1 || (scene) == SCENE_COTTAGE_MY)

#define mSc_IS_SCENE_BASEMENT(scene)                                               \
    ((scene) == SCENE_MY_ROOM_BASEMENT_S || (scene) == SCENE_MY_ROOM_BASEMENT_M || \
     (scene) == SCENE_MY_ROOM_BASEMENT_L || (scene) == SCENE_MY_ROOM_BASEMENT_LL1)

#define mSc_IS_SCENE_MUSEUM_ROOM(scene) ((scene) >= SCENE_MUSEUM_ENTRANCE && (scene) <= SCENE_MUSEUM_ROOM_FISH)

extern Scene_data_status_c scene_data_status[SCENE_NUM];

#ifdef __cplusplus
}
#endif

#endif
