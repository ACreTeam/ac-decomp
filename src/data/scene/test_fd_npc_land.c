#include "m_scene.h"

extern Actor_data TEST_FD_NPC_LAND_player_data[];
extern s16 TEST_FD_NPC_LAND_ctrl_actor_data[];
extern Actor_data TEST_FD_NPC_LAND_actor_data[];
extern s16 TEST_FD_NPC_LAND_object_bank[];

extern Scene_Word_u test_fd_npc_land_info[] = {
    mSc_DATA_SOUND(0, 0),                                       // Sound data
    mSc_DATA_PLAYER(TEST_FD_NPC_LAND_player_data),              // Player Data
    mSc_DATA_CTRL_ACTORS(17, TEST_FD_NPC_LAND_ctrl_actor_data), // Control actors
    mSc_DATA_ACTORS(2, TEST_FD_NPC_LAND_actor_data),            // Player Data
    mSc_DATA_OBJ_BANK(2, TEST_FD_NPC_LAND_object_bank),         // Required object banks
    mSc_DATA_FIELDCT(mSc_ITEM_TYPE_BGITEM, 4, 0x1C00, mSc_ROOM_TYPE_OUTDOORS,
                     FIELD_DRAW_TYPE_OUTDOORS), // Field construct params
    mSc_DATA_END(),                             // End of scene data
};

extern Actor_data TEST_FD_NPC_LAND_player_data[] = {
    {
        mAc_PROFILE_PLAYER, // profile
        { 2240, 0, 1600 },  // position
        { 0, 0, 0 },        // rotation
        0                   // ct arg
    },
};

extern s16 TEST_FD_NPC_LAND_ctrl_actor_data[] = {
    mAc_PROFILE_EFFECTBG,        // 0
    mAc_PROFILE_BIRTH_CONTROL,   // 1
    mAc_PROFILE_NPC,             // 2
    mAc_PROFILE_STRUCTURE,       // 3
    mAc_PROFILE_INSECT,          // 4
    mAc_PROFILE_TOOLS,           // 5
    mAc_PROFILE_HANDOVERITEM,    // 6
    mAc_PROFILE_EFFECT_CONTROL,  // 7
    mAc_PROFILE_SHOP_LEVEL,      // 8
    mAc_PROFILE_QUEST_MANAGER,   // 9
    mAc_PROFILE_EVENT_MANAGER,   // 10
    mAc_PROFILE_WEATHER,         // 11
    mAc_PROFILE_SET_MANAGER,     // 12
    mAc_PROFILE_GYOEI,           // 13
    mAc_PROFILE_SET_NPC_MANAGER, // 14
    mAc_PROFILE_BALL,            // 15
    mAc_PROFILE_MSCORE_CONTROL,  // 16
};

extern Actor_data TEST_FD_NPC_LAND_actor_data[] = {
    {
        mAc_PROFILE_UKI, // profile
        { 340, 0, 430 }, // position
        { 0, 0, 0 },     // rotation
        -1               // ct arg
    },
    {
        mAc_PROFILE_AC_SIGN, // profile
        { 0, 0, 0 },         // position
        { 0, 0, 0 },         // rotation
        -1                   // ct arg
    },
};

extern s16 TEST_FD_NPC_LAND_object_bank[] = {
    ACTOR_OBJ_BANK_48,      // 0
    ACTOR_OBJ_BANK_AC_SIGN, // 1
};
