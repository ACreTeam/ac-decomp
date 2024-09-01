#include "m_scene.h"

extern Door_data_c START_DEMO1_door_data[];
extern Actor_data START_DEMO1_player_data[];
extern s16 START_DEMO1_ctrl_actor_data[];

extern Scene_Word_u start_demo1_info[] = {
    mSc_DATA_SOUND(0, 0),                                 // Sound data
    mSc_DATA_DOOR_DATA(1, START_DEMO1_door_data),         // Door data
    mSc_DATA_PLAYER(START_DEMO1_player_data),             // Player Data
    mSc_DATA_ARRANGE_FTR(8),                              // Arrange furniture params
    mSc_DATA_ARRANGE_ROOM_CT(),                           // Arrange_room construct
    mSc_DATA_CTRL_ACTORS(6, START_DEMO1_ctrl_actor_data), // Control actors
    mSc_DATA_FIELDCT(mSc_ITEM_TYPE_BGITEM, 1, 0x7800, mSc_ROOM_TYPE_MISC_ROOM,
                     FIELD_DRAW_TYPE_TRAIN), // Field construct params
    mSc_DATA_END(),                          // End of scene data
};

extern Actor_data START_DEMO1_player_data[] = {
    {
        mAc_PROFILE_PLAYER, // profile
        { 120, 0, 340 },    // position
        { 0, 0, 0 },        // rotation
        0                   // ct arg
    },
};

extern s16 START_DEMO1_ctrl_actor_data[] = {
    mAc_PROFILE_BIRTH_CONTROL,  // 0
    mAc_PROFILE_NPC2,           // 1
    mAc_PROFILE_TOOLS,          // 2
    mAc_PROFILE_EFFECT_CONTROL, // 3
    mAc_PROFILE_QUEST_MANAGER,  // 4
    mAc_PROFILE_WEATHER,        // 5
};

extern Door_data_c START_DEMO1_door_data[] = {
    {
        SCENE_FG,           // scene
        1,                  // exit orientation
        0,                  // exit type
        0,                  // arg
        { 1979, 200, 760 }, // exit position
        0x0000,             // exit door item name
        2,                  // wipe type
        { 0, 0, 0 },        // padding
    },
};
