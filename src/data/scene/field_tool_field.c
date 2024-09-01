#include "m_scene.h"

extern Actor_data FIELD_TOOL_FIELD_player_data[];
extern s16 FIELD_TOOL_FIELD_ctrl_actor_data[];
extern Actor_data FIELD_TOOL_FIELD_actor_data[];
extern s16 FIELD_TOOL_FIELD_object_bank[];

extern Scene_Word_u field_tool_field_info[] = {
    mSc_DATA_SOUND(0, 0),                                      // Sound data
    mSc_DATA_PLAYER(FIELD_TOOL_FIELD_player_data),             // Player Data
    mSc_DATA_CTRL_ACTORS(9, FIELD_TOOL_FIELD_ctrl_actor_data), // Control actors
    mSc_DATA_ACTORS(1, FIELD_TOOL_FIELD_actor_data),           // Player Data
    mSc_DATA_OBJ_BANK(1, FIELD_TOOL_FIELD_object_bank),        // Required object banks
    mSc_DATA_FIELDCT(mSc_ITEM_TYPE_BGITEM, 4, 0x2800, mSc_ROOM_TYPE_OUTDOORS,
                     FIELD_DRAW_TYPE_OUTDOORS), // Field construct params
    mSc_DATA_END(),                             // End of scene data
};

extern Actor_data FIELD_TOOL_FIELD_player_data[] = {
    {
        mAc_PROFILE_PLAYER, // profile
        { 2240, 0, 1600 },  // position
        { 0, 0, 0 },        // rotation
        0                   // ct arg
    },
};

extern s16 FIELD_TOOL_FIELD_ctrl_actor_data[] = {
    mAc_PROFILE_EFFECTBG,       // 0
    mAc_PROFILE_BIRTH_CONTROL,  // 1
    mAc_PROFILE_NPC,            // 2
    mAc_PROFILE_STRUCTURE,      // 3
    mAc_PROFILE_TOOLS,          // 4
    mAc_PROFILE_HANDOVERITEM,   // 5
    mAc_PROFILE_EFFECT_CONTROL, // 6
    mAc_PROFILE_WEATHER,        // 7
    mAc_PROFILE_QUEST_MANAGER,  // 8
};

extern Actor_data FIELD_TOOL_FIELD_actor_data[] = {
    {
        mAc_PROFILE_UKI, // profile
        { 340, 0, 430 }, // position
        { 0, 0, 0 },     // rotation
        -1               // ct arg
    },
};

extern s16 FIELD_TOOL_FIELD_object_bank[] = {
    ACTOR_OBJ_BANK_48, // 0
};
