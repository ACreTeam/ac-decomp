#include "m_scene.h"

extern Door_data_c BUGGY_door_data[];
extern Actor_data BUGGY_player_data[];
extern s16 BUGGY_ctrl_actor_data[];

extern Scene_Word_u buggy_info[] = {
    mSc_DATA_SOUND(0, 0),                           // Sound data
    mSc_DATA_DOOR_DATA(1, BUGGY_door_data),         // Door data
    mSc_DATA_PLAYER(BUGGY_player_data),             // Player Data
    mSc_DATA_CTRL_ACTORS(8, BUGGY_ctrl_actor_data), // Control actors
    mSc_DATA_FIELDCT(mSc_ITEM_TYPE_BGITEM, 1, 0xA000, mSc_ROOM_TYPE_MISC_ROOM,
                     FIELD_DRAW_TYPE_INDOORS), // Field construct params
    mSc_DATA_END(),                            // End of scene data
};

extern Actor_data BUGGY_player_data[] = {
    {
        mAc_PROFILE_PLAYER, // profile
        { 160, 0, 260 },    // position
        { 0, -32768, 0 },   // rotation
        0                   // ct arg
    },
};

extern s16 BUGGY_ctrl_actor_data[] = {
    mAc_PROFILE_BIRTH_CONTROL,  // 0
    mAc_PROFILE_NPC2,           // 1
    mAc_PROFILE_TOOLS,          // 2
    mAc_PROFILE_EFFECT_CONTROL, // 3
    mAc_PROFILE_SHOP_LEVEL,     // 4
    mAc_PROFILE_QUEST_MANAGER,  // 5
    mAc_PROFILE_EVENT_MANAGER,  // 6
    mAc_PROFILE_WEATHER,        // 7
};

extern Door_data_c BUGGY_door_data[] = {
    {
        SCENE_FG,         // scene
        1,                // exit orientation
        0,                // exit type
        0,                // arg
        { 1600, 0, 740 }, // exit position
        0x0000,           // exit door item name
        2,                // wipe type
        { 0, 0, 0 },      // padding
    },
};
