#include "m_scene.h"

extern Actor_data BG_TEST01_XLU_player_data[];
extern s16 BG_TEST01_XLU_ctrl_actor_data[];

extern Scene_Word_u BG_TEST01_XLU_info[] = {
    mSc_DATA_SOUND(0, 0),                                    // Sound data
    mSc_DATA_PLAYER(BG_TEST01_XLU_player_data),              // Player Data
    mSc_DATA_CTRL_ACTORS(11, BG_TEST01_XLU_ctrl_actor_data), // Control actors
    mSc_DATA_FIELDCT(mSc_ITEM_TYPE_BGITEM, 4, 0x7800, mSc_ROOM_TYPE_OUTDOORS,
                     FIELD_DRAW_TYPE_OUTDOORS), // Field construct params
    mSc_DATA_END(),                             // End of scene data
};

extern Actor_data BG_TEST01_XLU_player_data[] = {
    {
        mAc_PROFILE_PLAYER, // profile
        { 340, 0, 430 },    // position
        { 0, 0, 0 },        // rotation
        0                   // ct arg
    },
};

extern s16 BG_TEST01_XLU_ctrl_actor_data[] = {
    mAc_PROFILE_BIRTH_CONTROL,  // 0
    mAc_PROFILE_NPC,            // 1
    mAc_PROFILE_STRUCTURE,      // 2
    mAc_PROFILE_INSECT,         // 3
    mAc_PROFILE_TOOLS,          // 4
    mAc_PROFILE_HANDOVERITEM,   // 5
    mAc_PROFILE_EFFECT_CONTROL, // 6
    mAc_PROFILE_SHOP_LEVEL,     // 7
    mAc_PROFILE_QUEST_MANAGER,  // 8
    mAc_PROFILE_EVENT_MANAGER,  // 9
    mAc_PROFILE_WEATHER,        // 10
};
