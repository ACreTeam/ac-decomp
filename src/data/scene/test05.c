#include "m_scene.h"

extern Actor_data TEST05_player_data[];
extern s16 TEST05_ctrl_actor_data[];

extern Scene_Word_u test05_info[] = {
    mSc_DATA_SOUND(0, 0),                            // Sound data
    mSc_DATA_PLAYER(TEST05_player_data),             // Player Data
    mSc_DATA_CTRL_ACTORS(5, TEST05_ctrl_actor_data), // Control actors
    mSc_DATA_FIELDCT(mSc_ITEM_TYPE_BGITEM, 4, 0x5000, mSc_ROOM_TYPE_OUTDOORS,
                     FIELD_DRAW_TYPE_OUTDOORS), // Field construct params
    mSc_DATA_END(),                             // End of scene data
};

extern Actor_data TEST05_player_data[] = {
    {
        mAc_PROFILE_PLAYER, // profile
        { 340, 0, 430 },    // position
        { 0, 0, 0 },        // rotation
        0                   // ct arg
    },
};

extern s16 TEST05_ctrl_actor_data[] = {
    mAc_PROFILE_EFFECTBG,       // 0
    mAc_PROFILE_BIRTH_CONTROL,  // 1
    mAc_PROFILE_HANDOVERITEM,   // 2
    mAc_PROFILE_EFFECT_CONTROL, // 3
    mAc_PROFILE_WEATHER,        // 4
};
