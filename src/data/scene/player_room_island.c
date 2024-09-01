#include "m_scene.h"

extern Door_data_c PLAYER_ROOM_ISLAND_door_data[];
extern Actor_data PLAYER_ROOM_ISLAND_player_data[];
extern s16 PLAYER_ROOM_ISLAND_ctrl_actor_data[];
extern Actor_data PLAYER_ROOM_ISLAND_actor_data[];
extern s16 PLAYER_ROOM_ISLAND_object_bank[];

extern Scene_Word_u player_room_island_info[] = {
    mSc_DATA_SOUND(0, 1),                                         // Sound data
    mSc_DATA_DOOR_DATA(1, PLAYER_ROOM_ISLAND_door_data),          // Door data
    mSc_DATA_PLAYER(PLAYER_ROOM_ISLAND_player_data),              // Player Data
    mSc_DATA_ARRANGE_FTR(48),                                     // Arrange furniture params
    mSc_DATA_CTRL_ACTORS(12, PLAYER_ROOM_ISLAND_ctrl_actor_data), // Control actors
    mSc_DATA_ACTORS(2, PLAYER_ROOM_ISLAND_actor_data),            // Player Data
    mSc_DATA_OBJ_BANK(2, PLAYER_ROOM_ISLAND_object_bank),         // Required object banks
    mSc_DATA_FIELDCT(mSc_ITEM_TYPE_DUMMY, 1, 0xA000, mSc_ROOM_TYPE_MY_ROOM,
                     FIELD_DRAW_TYPE_INDOORS), // Field construct params
    mSc_DATA_END(),                            // End of scene data
};

extern Actor_data PLAYER_ROOM_ISLAND_player_data[] = {
    {
        mAc_PROFILE_PLAYER, // profile
        { 160, 0, 200 },    // position
        { 0, 0, 0 },        // rotation
        0                   // ct arg
    },
};

extern s16 PLAYER_ROOM_ISLAND_ctrl_actor_data[] = {
    mAc_PROFILE_BIRTH_CONTROL,  // 0
    mAc_PROFILE_NPC2,           // 1
    mAc_PROFILE_INSECT,         // 2
    mAc_PROFILE_TOOLS,          // 3
    mAc_PROFILE_HANDOVERITEM,   // 4
    mAc_PROFILE_EFFECT_CONTROL, // 5
    mAc_PROFILE_SHOP_LEVEL,     // 6
    mAc_PROFILE_QUEST_MANAGER,  // 7
    mAc_PROFILE_EVENT_MANAGER,  // 8
    mAc_PROFILE_WEATHER,        // 9
    mAc_PROFILE_MY_ROOM,        // 10
    mAc_PROFILE_MY_INDOOR,      // 11
};

extern Actor_data PLAYER_ROOM_ISLAND_actor_data[] = {
    {
        mAc_PROFILE_ROOM_SUNSHINE, // profile
        { 40, 0, 200 },            // position
        { 0, 0, 0 },               // rotation
        2                          // ct arg
    },
    {
        mAc_PROFILE_ROOM_SUNSHINE, // profile
        { 360, 0, 200 },           // position
        { 0, 0, 0 },               // rotation
        3                          // ct arg
    },
};

extern s16 PLAYER_ROOM_ISLAND_object_bank[] = {
    ACTOR_OBJ_BANK_ROOM_SUNSHINE, // 0
    ACTOR_OBJ_BANK_369,           // 1
};

extern Door_data_c PLAYER_ROOM_ISLAND_door_data[] = {
    {
        SCENE_MY_ROOM_BASEMENT_M, // scene
        6,                        // exit orientation
        0,                        // exit type
        0,                        // arg
        { 300, 0, 380 },          // exit position
        0x4000,                   // exit door item name
        2,                        // wipe type
        { 0, 0, 0 },              // padding
    },
};
