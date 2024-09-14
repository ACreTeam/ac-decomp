#include "m_scene.h"

extern Door_data_c SHOP01_door_data[];
extern Actor_data SHOP01_player_data[];
extern s16 SHOP01_ctrl_actor_data[];
extern s16 SHOP01_object_bank[];

extern Scene_Word_u shop01_info[] = {
    mSc_DATA_SOUND(0, 0),                             // Sound data
    mSc_DATA_DOOR_DATA(1, SHOP01_door_data),          // Door data
    mSc_DATA_PLAYER(SHOP01_player_data),              // Player Data
    mSc_DATA_ARRANGE_FTR(6),                          // Arrange furniture params
    mSc_DATA_CTRL_ACTORS(16, SHOP01_ctrl_actor_data), // Control actors
    mSc_DATA_OBJ_BANK(1, SHOP01_object_bank),         // Required object banks
    mSc_DATA_FIELDCT(mSc_ITEM_TYPE_DUMMY, 1, 0xA000, mSc_ROOM_TYPE_MISC_ROOM,
                     FIELD_DRAW_TYPE_INDOORS), // Field construct params
    mSc_DATA_END(),                            // End of scene data
};

extern Actor_data SHOP01_player_data[] = {
    {
        mAc_PROFILE_PLAYER, // profile
        { 160, 0, 300 },    // position
        { 0, -32768, 0 },   // rotation
        0                   // ct arg
    },
};

extern s16 SHOP01_ctrl_actor_data[] = {
    mAc_PROFILE_BIRTH_CONTROL,  // 0
    mAc_PROFILE_SHOP_DESIGN,    // 1
    mAc_PROFILE_NPC2,           // 2
    mAc_PROFILE_INSECT,         // 3
    mAc_PROFILE_TOOLS,          // 4
    mAc_PROFILE_HANDOVERITEM,   // 5
    mAc_PROFILE_EFFECT_CONTROL, // 6
    mAc_PROFILE_SHOP_LEVEL,     // 7
    mAc_PROFILE_QUEST_MANAGER,  // 8
    mAc_PROFILE_EVENT_MANAGER,  // 9
    mAc_PROFILE_WEATHER,        // 10
    mAc_PROFILE_HOUSE_CLOCK,    // 11
    mAc_PROFILE_MY_ROOM,        // 12
    mAc_PROFILE_SHOP_MANEKIN,   // 13
    mAc_PROFILE_SHOP_INDOOR,    // 14
    mAc_PROFILE_SHOP_UMBRELLA,  // 15
};

extern s16 SHOP01_object_bank[] = {
    ACTOR_OBJ_BANK_13, // 0
};

extern Door_data_c SHOP01_door_data[] = {
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
