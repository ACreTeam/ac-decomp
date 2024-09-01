#include "m_scene.h"

extern Actor_data TEST01_player_data[];
extern s16 TEST01_ctrl_actor_data[];
extern Actor_data TEST01_actor_data[];
extern s16 TEST01_object_bank[];

extern Scene_Word_u test01_info[] = {
    mSc_DATA_SOUND(0, 0),                             // Sound data
    mSc_DATA_PLAYER(TEST01_player_data),              // Player Data
    mSc_DATA_CTRL_ACTORS(12, TEST01_ctrl_actor_data), // Control actors
    mSc_DATA_ACTORS(2, TEST01_actor_data),            // Player Data
    mSc_DATA_OBJ_BANK(1, TEST01_object_bank),         // Required object banks
    mSc_DATA_FIELDCT(mSc_ITEM_TYPE_BGITEM, 4, 0x5000, mSc_ROOM_TYPE_OUTDOORS,
                     FIELD_DRAW_TYPE_OUTDOORS), // Field construct params
    mSc_DATA_END(),                             // End of scene data
};

extern Actor_data TEST01_player_data[] = {
    {
        mAc_PROFILE_PLAYER, // profile
        { 340, 0, 430 },    // position
        { 0, 0, 0 },        // rotation
        0                   // ct arg
    },
};

extern s16 TEST01_ctrl_actor_data[] = {
    mAc_PROFILE_EFFECTBG,       // 0
    mAc_PROFILE_BIRTH_CONTROL,  // 1
    mAc_PROFILE_NPC,            // 2
    mAc_PROFILE_STRUCTURE,      // 3
    mAc_PROFILE_INSECT,         // 4
    mAc_PROFILE_TOOLS,          // 5
    mAc_PROFILE_HANDOVERITEM,   // 6
    mAc_PROFILE_EFFECT_CONTROL, // 7
    mAc_PROFILE_QUEST_MANAGER,  // 8
    mAc_PROFILE_EVENT_MANAGER,  // 9
    mAc_PROFILE_WEATHER,        // 10
    mAc_PROFILE_BALL,           // 11
};

extern Actor_data TEST01_actor_data[] = {
    {
        mAc_PROFILE_UKI, // profile
        { 340, 0, 430 }, // position
        { 0, 0, 0 },     // rotation
        -1               // ct arg
    },
    {
        mAc_PROFILE_FUUSEN, // profile
        { 340, 0, 430 },    // position
        { 0, 0, 0 },        // rotation
        -1                  // ct arg
    },
};

extern s16 TEST01_object_bank[] = {
    ACTOR_OBJ_BANK_FUUSEN, // 0
};
