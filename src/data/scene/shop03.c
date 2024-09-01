#include "m_scene.h"

extern Door_data_c SHOP03_door_data[];
extern Actor_data SHOP03_player_data[];
extern s16 SHOP03_ctrl_actor_data[];

extern Scene_Word_u shop03_info[] = {
    mSc_DATA_SOUND(0, 0),                             // Sound data
    mSc_DATA_DOOR_DATA(1, SHOP03_door_data),          // Door data
    mSc_DATA_PLAYER(SHOP03_player_data),              // Player Data
    mSc_DATA_ARRANGE_FTR(6),                          // Arrange furniture params
    mSc_DATA_CTRL_ACTORS(15, SHOP03_ctrl_actor_data), // Control actors
    mSc_DATA_FIELDCT(mSc_ITEM_TYPE_DUMMY, 1, 0xA000, mSc_ROOM_TYPE_MISC_ROOM,
                     FIELD_DRAW_TYPE_INDOORS), // Field construct params
    mSc_DATA_END(),                            // End of scene data
};

extern Actor_data SHOP03_player_data[] = {
    {
        mAc_PROFILE_PLAYER, // profile
        { 320, 0, 460 },    // position
        { 0, -32768, 0 },   // rotation
        0                   // ct arg
    },
};

extern s16 SHOP03_ctrl_actor_data[] = {
    mAc_PROFILE_BIRTH_CONTROL,  // 0
    mAc_PROFILE_SHOP_DESIGN,    // 1
    mAc_PROFILE_TOOLS,          // 2
    mAc_PROFILE_HANDOVERITEM,   // 3
    mAc_PROFILE_EFFECT_CONTROL, // 4
    mAc_PROFILE_SHOP_LEVEL,     // 5
    mAc_PROFILE_QUEST_MANAGER,  // 6
    mAc_PROFILE_EVENT_MANAGER,  // 7
    mAc_PROFILE_WEATHER,        // 8
    mAc_PROFILE_HOUSE_CLOCK,    // 9
    mAc_PROFILE_MY_ROOM,        // 10
    mAc_PROFILE_SHOP_MANEKIN,   // 11
    mAc_PROFILE_SHOP_INDOOR,    // 12
    mAc_PROFILE_SHOP_UMBRELLA,  // 13
    mAc_PROFILE_NPC2,           // 14
};

extern Door_data_c SHOP03_door_data[] = {
    {
        SCENE_TEST2,     // scene
        1,               // exit orientation
        0,               // exit type
        0,               // arg
        { 40, 0, 1730 }, // exit position
        0x0000,          // exit door item name
        2,               // wipe type
        { 0, 0, 0 },     // padding
    },
};
