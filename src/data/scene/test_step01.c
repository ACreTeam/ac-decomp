#include "m_scene.h"

extern Actor_data TEST_STEP01_player_data[];

extern Scene_Word_u test_step01_info[] = {
    mSc_DATA_SOUND(0, 0),                     // Sound data
    mSc_DATA_PLAYER(TEST_STEP01_player_data), // Player Data
    mSc_DATA_FIELDCT(mSc_ITEM_TYPE_BGITEM, 4, 0x5000, mSc_ROOM_TYPE_OUTDOORS,
                     FIELD_DRAW_TYPE_OUTDOORS), // Field construct params
    mSc_DATA_END(),                             // End of scene data
};

extern Actor_data TEST_STEP01_player_data[] = {
    {
        mAc_PROFILE_PLAYER, // profile
        { 160, 0, 300 },    // position
        { 0, 0, 0 },        // rotation
        0                   // ct arg
    },
};
